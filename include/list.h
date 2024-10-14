#ifndef ARCHIVE_LIST
#define ARCHIVE_LIST

struct archive_list_node {
    struct archive_list_node *next;
    const char *file_name;
    char *data; // heap allocated
    int data_len;
};

struct archive_list {
    struct archive_list_node *head;
    int file_count;
};

struct archive_list *archive_list_init();
int archive_list_add(struct archive_list *list, const char *file_path);
// Copies `data_len` bytes in `data` into a seperate heap allocated buffer for storing
int archive_list_add_bytes(struct archive_list *list, char *data, int data_len);
void archive_list_destroy(struct archive_list *list);

#endif