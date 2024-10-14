#include "../include/list.h"
#include <stdlib.h>

struct archive_list *archive_list_init() { return NULL; }

int archive_list_add(struct archive_list *list, const char *file_name,
                     unsigned int offset, int len)
{
    return 0;
}

void archive_list_destroy(struct archive_list *list) {}