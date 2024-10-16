#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "list.h"
#include <stdio.h>

typedef struct {
    const char *archive_file_path;
    FILE *stream;
    struct archive_list *files;
} archive_ctx_t;

archive_ctx_t *archive_init(const char *archive_file_path);

// Creates the archive file and marks it as our custom file
int archive_create(archive_ctx_t *ctx);
// Writes the file in `file_path` to the archive
int archive_add(archive_ctx_t *ctx, const char *file_path);

// Reads the archive file and parses the information about the archive
int archive_read(archive_ctx_t *ctx);
// Extracts the file from the archive by `file_index` to `file_path_out`
int archive_extract(archive_ctx_t *ctx, int file_index,
                    const char *file_path_out);

void archive_destroy(archive_ctx_t *ctx);

#endif