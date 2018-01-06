#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "u_datalist.h"

#define DATALIST_INFO(...)

#define DATALIST_ERR(...) \
    do \
    { \
        printf("<DATLIST>[%s:%d]:", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__); \
    } \
    while (0)

void u_datalist_init(DATALIST_T *list_head)
{
    assert(list_head);
    list_head->head = NULL;
}

int u_datalist_enqueue(DATALIST_T *list_head, void *data, size_t size, int id)
{
    assert(list_head);

    DATANODE_T *list_temp = list_head->head;
    DATANODE_T *node = (DATANODE_T *)calloc(sizeof(DATANODE_T), 1);
    if (NULL == node)
    {
        DATALIST_ERR("malloc node failed!\n");
        goto MALLOC_NODE_ERR;
    }

    if (data && size)
    {
        node->data = malloc(size);
        if (NULL == node->data)
        {
            DATALIST_ERR("malloc data failed!\n");
            goto MALLOC_DATA_ERR;
        }
        memcpy(node->data, data, size);
        node->size = size;
    }

    node->id = id;
    node->next = NULL;

    if (NULL == list_temp)
    {
        list_head->head = node;
    }
    else
    {
        while (list_temp->next)
        {
            list_temp = list_temp->next;
        }
        list_temp->next = node;
    }

    return DATALIST_SUCCESS;

MALLOC_DATA_ERR:
    free(node);
MALLOC_NODE_ERR:
    return DATALIST_FAIL;
}

int u_datalist_head_enqueue(DATALIST_T *list_head, void *data, size_t size, int id)
{
    assert(list_head);

   DATANODE_T *node = (DATANODE_T *)calloc(sizeof(DATANODE_T), 1);
    if (NULL == node)
    {
        DATALIST_ERR("malloc node failed!\n");
        goto MALLOC_NODE_ERR;
    }

    if (data && size)
    {
        node->data = malloc(size);
        if (NULL == node->data)
        {
            DATALIST_ERR("malloc data failed!\n");
            goto MALLOC_DATA_ERR;
        }
        memcpy(node->data, data, size);
        node->size = size;
    }

    node->id = id;
    node->next = list_head->head;
    list_head->head = node;

    return DATALIST_SUCCESS;

MALLOC_DATA_ERR:
    free(node);
MALLOC_NODE_ERR:
    return DATALIST_FAIL;
}

DATANODE_T *u_datalist_dequeue(DATALIST_T *list_head)
{
    assert(list_head);
    if (NULL == list_head->head)
    {
        DATALIST_INFO("list is empty!\n");
        return NULL;
    }

    DATANODE_T *node = list_head->head;
    list_head->head = node->next;

    return node;
}

void u_datanode_free(DATANODE_T *node)
{
    if (NULL == node)
    {
        return;
    }

    if (node->data)
    {
        free(node->data);
    }
    free(node);
}

void u_datalist_destroy(DATALIST_T *list_head)
{
    DATANODE_T *pt_node;
    assert(list_head);
    if (NULL == list_head->head)
    {
        return;
    }

    while (pt_node = u_datalist_dequeue(list_head))
    {
        u_datanode_free(pt_node);
    }
}

int u_datalist_is_empty(DATALIST_T *list_head)
{
    return (!(list_head->head));
}

