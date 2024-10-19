#include "include/archive.h"
#include "include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int args = argc - 1;
    if (args < 2) {
        fprintf(stderr, "Unknown option. Try again.\n");
        return 1;
    }

    const char *action = argv[1];
    const char *archive_file = argv[2];

    archive_ctx_t *ctx = archive_init(archive_file);
    if (!ctx) {
        fprintf(stderr, "Failed to initialize the archive.\n");
        return 1;
    }

    if (strcmp(action, "x") == 0) {
        /* Extract */
        if (args != 4)
            goto unk_option;

        if (archive_read(ctx) != 0) {
            fprintf(stderr, "Failed to read the archive file.\n");
            goto cleanup;
        }

        unsigned int index = (unsigned int)atoi(argv[3]);
        const char *path_to = argv[4];

        if (archive_extract(ctx, index, path_to) != 0) {
            fprintf(stderr, "failed to extract the file.\n");
            goto cleanup;
        }
    }
    else if (strcmp(action, "xa") == 0) {
        /* Extract all into a directory */
        if (args != 3)
            goto unk_option;

        if (archive_read(ctx) != 0) {
            fprintf(stderr, "Failed to read the archive file.\n");
            goto cleanup;
        }

        const char *dir = argv[3];

        archive_list_node_t *node = ctx->files->head;
        while (node) {
            char path_to[1024];
            snprintf(path_to, sizeof(path_to), "%s%s", dir, node->file_name);
            if (archive_extract_by_offset(ctx, node->offset, path_to) != 0) {
                fprintf(stderr, "Failed to extract the files.\n");
                goto cleanup;
            }
            node = node->next;
        }
    }
    else if (strcmp(action, "l") == 0) {
        /* List */
        if (archive_read(ctx) != 0) {
            fprintf(stderr, "Failed to read the archive file.\n");
            goto cleanup;
        }

        fprintf(stdout, "Files in the archive: %u\n", ctx->files->file_count);

        archive_list_node_t *node = ctx->files->head;
        while (node) {
            fprintf(stdout,
                    "File name: %s, length: %zu, offset in archive: %zx\n",
                    node->file_name, node->len, node->offset);
            node = node->next;
        }
    }
    else if (strcmp(action, "a") == 0) {
        /* Archive */
        if (args < 3) {
            fprintf(stderr, "Specify files for archiving.\n");
            goto cleanup;
        }

        if (archive_create(ctx) != 0) {
            fprintf(stderr, "Failed to create an archive file.\n");
            goto cleanup;
        }

        for (int i = 3; i < argc; i++) {
            if (archive_add(ctx, argv[i]) != 0) {
                fprintf(stderr, "Failed to add the file in the archive.\n");
                goto cleanup;
            }
        }
    }
    else {
    unk_option:
        fprintf(stderr, "Unknown option. Try again.\n");
    cleanup:
        archive_destroy(ctx);
        return 1;
    }

    archive_destroy(ctx);
    return 0;
}