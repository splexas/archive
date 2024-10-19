#include "include/archive.h"
#include "include/list.h"
#include <stdio.h>

void a(archive_ctx_t *ctx)
{
    archive_create(ctx);
    printf("%d\n", archive_add(ctx, "./files/file.txt"));
    printf("%d\n", archive_add(ctx, "./files/test.txt"));
    archive_destroy(ctx);
}

void b(archive_ctx_t *ctx)
{
    printf("archive_read: %d\n", archive_read(ctx));
    printf("files read: %d\n", ctx->files->file_count);
    archive_destroy(ctx);
}

int main(int argc, char *argv[])
{
    archive_ctx_t *ctx;
    
    ctx = archive_init("./test.archive");
    a(ctx);

    ctx = archive_init("./test.archive");
    b(ctx);

    return 0;
}