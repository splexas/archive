#include "../include/list.h"
#include <stdlib.h>
#include <string.h>

archive_list_t *archive_list_init()
{
    archive_list_t *list = (archive_list_t *)malloc(sizeof(archive_list_t));
    if (!list)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->file_count = 0;
    return list;
}

int archive_list_add(archive_list_t *list, const char *file_name, size_t offset,
                     size_t len)
{
    archive_list_node_t *new_node =
        (archive_list_node_t *)malloc(sizeof(archive_list_node_t));
    if (!new_node)
        return 1;

    char *dup = strdup(file_name);
    if (!dup) {
        free(new_node);
        return 1;
    }

    new_node->next = NULL;
    new_node->file_name = dup;
    new_node->offset = offset;
    new_node->len = len;

    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->file_count++;
    return 0;
}

archive_list_node_t *archive_list_get(archive_list_t *list, unsigned int index)
{
    archive_list_node_t *node = list->head;
    unsigned int i = 0;

    while (node) {
        if (i == index)
            return node;
        node = node->next;
        i++;
    }

    return NULL;
}

void archive_list_destroy(archive_list_t *list)
{
    archive_list_node_t *node = list->head;
    archive_list_node_t *prev = NULL;

    while (node) {
        prev = node;
        node = node->next;
        free((void *)prev->file_name);
        free(prev);
    }

    free(list);
}