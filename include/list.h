#ifndef ARCHIVE_LIST
#define ARCHIVE_LIST

typedef struct archive_list_node {
    struct archive_list_node *next;
    const char *file_name;
    unsigned int offset;
    int len;
} archive_list_node_t;

typedef struct {
    archive_list_node_t *head;
    int file_count;
} archive_list_t;

archive_list_t *archive_list_init();
int archive_list_add(archive_list_t *list, const char *file_name,
                     unsigned int offset, int len);
void archive_list_destroy(archive_list_t *list);

#endif