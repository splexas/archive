#include "../include/archive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char MARK[] = "ARCHIVE";

archive_ctx_t *archive_init(const char *archive_file_path)
{
    archive_ctx_t *ctx = (archive_ctx_t *)malloc(sizeof(archive_ctx_t));
    if (!ctx)
        return NULL;

    archive_list_t *list = archive_list_init();
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

    size_t written = fwrite((const void *)MARK, 1, sizeof(MARK) - 1, f);

    if (written != sizeof(MARK) - 1) {
        fclose(f);
        return 1;
    }

    ctx->stream = f;
    return 0;
}

static const char *archive_get_file_name(const char *path, int *file_len_out)
{
    int i = 0;
    int last = 0;

    while (path[i] != '\0') {
        if (path[i] == '/')
            last = i;

        i++;
    }

    *file_len_out = i - last - 1;
    return last == 0 ? path : path + last + 1;
}

int archive_add(archive_ctx_t *ctx, const char *file_path)
{
    int file_name_len = 0;
    const char *file_name = archive_get_file_name(file_path, &file_name_len);

    FILE *f = fopen(file_path, "rb");

    fseek(f, 0, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    size_t total_len = file_name_len + 1 + sizeof(size_t) * 2 + sz;

    if (fwrite(&total_len, 1, sizeof(size_t), ctx->stream) != sizeof(size_t)) {
        fclose(f);
        return 1;
    }

    if (fwrite(file_name, 1, file_name_len + 1, ctx->stream) !=
        (size_t)file_name_len + 1) {
        fclose(f);
        return 1;
    }

    if (fwrite(&sz, 1, sizeof(size_t), ctx->stream) != sizeof(size_t)) {
        fclose(f);
        return 1;
    }

    char c;
    while ((c = fgetc(f)) != EOF)
        fputc(c, ctx->stream);

    fclose(f);
    return 0;
}

// Moves file cursor by `MARK` len (no nulltermination)
static int archive_check_mark(FILE *f)
{
    char c;
    int i = 0;

    while ((c = fgetc(f)) != EOF) {
        if (c != MARK[i])
            break;

        if (i == sizeof(MARK) - 2)
            return 0;

        i++;
    }

    return 1;
}

int archive_read(archive_ctx_t *ctx)
{
    FILE *f = fopen(ctx->archive_file_path, "rb");
    if (!f)
        return 1;

    if (archive_check_mark(f) != 0) {
        fclose(f);
        return 1;
    }

    size_t total_len;

    while (fread(&total_len, 1, sizeof(total_len), f) && !feof(f)) {
        char file_name[256];
        size_t data_len;

        char c;
        int i = 0;
        while ((c = fgetc(f)) != 0) {
            file_name[i] = c;
            i++;
        }
        file_name[i] = 0;

        int a = fread(&data_len, 1, sizeof(data_len), f);
        if (a != sizeof(data_len)) {
            fclose(f);
            return 1;
        }

        if (archive_list_add(ctx->files, file_name, ftell(f), data_len) != 0) {
            fclose(f);
            return 1;
        }

        fseek(f, data_len, SEEK_CUR);
    }

    ctx->stream = f;
    return 0;
}

int archive_extract(archive_ctx_t *ctx, int file_index,
                    const char *file_path_out)
{
    return 0;
}

void archive_destroy(archive_ctx_t *ctx)
{
    if (ctx->stream)
        fclose(ctx->stream);

    archive_list_destroy(ctx->files);
    free(ctx);
}