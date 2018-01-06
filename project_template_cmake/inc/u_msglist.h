#ifndef __U_MSGLIST_H__
#define __U_MSGLIST_H__

#include <pthread.h>
#include "u_datalist.h"

#define MSGLIST_FAIL       -1
#define MSGLIST_SUCCESS    0

typedef struct
{
    unsigned int data_count;
    DATALIST_T list_head;
    pthread_mutex_t t_mutex;
    pthread_cond_t t_cond;
} MSGLIST_T;

extern int u_msglist_create(MSGLIST_T **ppt_list);
extern int u_msglist_send(MSGLIST_T *pt_list, void *data, size_t size, int id);
extern int u_msglist_head_send(MSGLIST_T *pt_list, void *data, size_t size, int id);
extern DATANODE_T *u_msglist_receive(MSGLIST_T *pt_list);
extern DATANODE_T *u_msglist_receive_timeout(MSGLIST_T *pt_list, unsigned int time);
extern unsigned int u_msglist_datacount(MSGLIST_T *pt_list);
extern void u_msglist_flush(MSGLIST_T *pt_list);
extern void u_msglist_destroy(MSGLIST_T **ppt_list);

#endif
