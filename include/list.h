#ifndef ARCHIVE_LIST
#define ARCHIVE_LIST

#include <stddef.h>

typedef struct archive_list_node {
    struct archive_list_node *next;
    const char *file_name;
    unsigned int offset;
    size_t len;
} archive_list_node_t;

typedef struct {
    archive_list_node_t *head;
    archive_list_node_t *tail;
    unsigned int file_count;
} archive_list_t;

archive_list_t *archive_list_init();
int archive_list_add(archive_list_t *list, const char *file_name,
                     unsigned int offset, size_t len);
archive_list_node_t *archive_list_get(archive_list_t *list, unsigned int index);
void archive_list_destroy(archive_list_t *list);

#endif