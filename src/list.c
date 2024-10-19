#include "../include/list.h"
#include <stdlib.h>
#include <string.h>

archive_list_t *archive_list_init()
{
    archive_list_t *list = (archive_list_t *)malloc(sizeof(archive_list_t));
    if (!list)
        return NULL;

    list->head = NULL;
    list->file_count = 0;
    return list;
}

int archive_list_add(archive_list_t *list, const char *file_name,
                     unsigned int offset, int len)
{
    archive_list_node_t *new_node =
        (archive_list_node_t *)malloc(sizeof(archive_list_node_t));
    if (!new_node)
        return 1;

    new_node->next = NULL;
    new_node->file_name = strdup(file_name);
    new_node->offset = offset;
    new_node->len = len;

    if (!list->head) {
        list->head = new_node;
    }
    else {
        archive_list_node_t *node = list->head;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }

    list->file_count++;
    return 0;
}

void archive_list_destroy(archive_list_t *list)
{
    if (!list->head)
        return;

    archive_list_node_t *prev = NULL;
    archive_list_node_t *node = list->head;

    while (node->next) {
        prev = node;
        node = node->next;
        free((void *)prev->file_name);
        free(prev);
    }

    free(list);
}