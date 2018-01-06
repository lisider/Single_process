#ifndef __U_DATALIST_H__
#define __U_DATALIST_H__

#define DATALIST_FAIL       -1
#define DATALIST_SUCCESS    0

typedef struct _datanode
{
    int    id;
    void   *data;
    size_t size;
    struct _datanode *next;
} DATANODE_T;

typedef struct
{
    DATANODE_T *head;
} DATALIST_T;

extern void u_datalist_init(DATALIST_T *list_head);
extern int  u_datalist_enqueue(DATALIST_T *list_head, void *data, size_t size, int id);
extern int u_datalist_head_enqueue(DATALIST_T *list_head, void *data, size_t size, int id);
extern DATANODE_T *u_datalist_dequeue(DATALIST_T *list_head);
extern void u_datanode_free(DATANODE_T *node);
extern void u_datalist_destroy(DATALIST_T *list_head);
extern int u_datalist_is_empty(DATALIST_T *list_head);

#endif
