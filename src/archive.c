#include "../include/archive.h"
#include <stdio.h>
#include <stdlib.h>

archive_ctx_t *archive_init(const char *archive_file_path)
{
    archive_ctx_t *ctx = (archive_ctx_t *)malloc(sizeof(archive_ctx_t));
    if (!ctx)
        return NULL;

    struct archive_list *list = archive_list_init();
    if (!list) {
        free(ctx);
        return NULL;
    }

    ctx->archive_file_path = archive_file_path;
    ctx->stream = NULL;
    ctx->files = list;
    return ctx;
}

int archive_create(archive_ctx_t *ctx)
{
    FILE *f = fopen(ctx->archive_file_path, "wb");
    if (!f)
        return 1;

    static const char MARK[] = "ARCHIVE";
    size_t written = fwrite((const void *)MARK, 1, sizeof(MARK) - 1, f);
    return !(written == sizeof(MARK) - 1);
}

int archive_add(archive_ctx_t *ctx, const char *file_path) { return 0; }

int archive_read(archive_ctx_t *ctx)
{
    FILE *f = fopen(ctx->archive_file_path, "rb");
    if (!f)
        return 1;

    // we check if file begins with ARCHIVE
    // logic

    return 0;
}

int archive_extract(archive_ctx_t *ctx, int file_index,
                    const char *file_path_out)
{
    return 0;
}

void archive_destroy(archive_ctx_t *ctx) {}