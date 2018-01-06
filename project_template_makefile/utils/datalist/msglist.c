#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "u_msglist.h"

#define MSGLIST_INFO(...)

#define MSGLIST_ERR(...) \
    do \
    { \
        printf("<MSGLIST>[%s:%d]:", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__); \
    } \
    while (0)

static int _msglist_transfer_time(struct timespec *abstime, unsigned int ui4_time)
{
    int i4_ret;
    i4_ret = clock_gettime(CLOCK_MONOTONIC, abstime);
    if (i4_ret)
    {
        MSGLIST_ERR("clock_gettime failed!\n");
        return MSGLIST_FAIL;
    }
    abstime->tv_sec  += ui4_time / 1000;
    ui4_time %= 1000;
    abstime->tv_nsec += ui4_time * 1000000;
    if (abstime->tv_nsec >= 1000000000)
    {
        abstime->tv_nsec -= 1000000000;
        abstime->tv_sec++;
    }
    return MSGLIST_SUCCESS;
}

int u_msglist_create(MSGLIST_T **ppt_list)
{
    int i4_ret;
    MSGLIST_T *pt_list;
    pthread_condattr_t condattr;

    if (!ppt_list)
    {
        MSGLIST_ERR("ppt_list can't be NULL!\n");
        return MSGLIST_FAIL;
    }

    *ppt_list = (MSGLIST_T *)calloc(sizeof(MSGLIST_T), 1);
    if (NULL == *ppt_list)
    {
        MSGLIST_ERR("calloc MSGLIST_T failed!\n");
        return MSGLIST_FAIL;
    }

    pt_list = *ppt_list;

    u_datalist_init(&pt_list->list_head);
    i4_ret = pthread_mutex_init(&pt_list->t_mutex, NULL);
    if (i4_ret)
    {
        MSGLIST_ERR("mutex init failed!\n");
        goto MUTEX_INIT_ERR;
    }
    i4_ret = pthread_condattr_init(&condattr);
    if (i4_ret)
    {
        MSGLIST_ERR("condattr init failed!\n");
        goto ATTR_INIT_ERR;
    }
    i4_ret = pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC);
    if (i4_ret)
    {
        MSGLIST_ERR("condattr setclock failed!\n");
        goto ATTR_INIT_ERR;
    }
    i4_ret = pthread_cond_init(&pt_list->t_cond, &condattr);
    if (i4_ret)
    {
        MSGLIST_ERR("cond init failed!\n");
        goto COND_INIT_ERR;
    }

    pt_list->data_count = 0;

    return MSGLIST_SUCCESS;
COND_INIT_ERR:
    pthread_condattr_destroy(&condattr);
ATTR_INIT_ERR:
    pthread_mutex_destroy(&pt_list->t_mutex);
MUTEX_INIT_ERR:
    free(*ppt_list);
    *ppt_list = NULL;
    return MSGLIST_FAIL;
}

int u_msglist_send(MSGLIST_T *pt_list, void *data, size_t size, int id)
{
    int i4_ret;

    if (!pt_list)
    {
        MSGLIST_ERR("pt_list can't be NULL!\n");
        return MSGLIST_FAIL;
    }

    pthread_mutex_lock(&pt_list->t_mutex);
    i4_ret = u_datalist_enqueue(&pt_list->list_head, data, size, id);
    if (i4_ret)
    {
        MSGLIST_ERR("datalist enqueue failed!\n");
        pthread_mutex_unlock(&pt_list->t_mutex);
        return MSGLIST_FAIL;
    }
    pt_list->data_count += size;
    pthread_cond_broadcast(&pt_list->t_cond);
    pthread_mutex_unlock(&pt_list->t_mutex);

    return MSGLIST_SUCCESS;
}

int u_msglist_head_send(MSGLIST_T *pt_list, void *data, size_t size, int id)
{
    int i4_ret;

    if (!pt_list)
    {
        MSGLIST_ERR("pt_list can't be NULL!\n");
        return MSGLIST_FAIL;
    }

    pthread_mutex_lock(&pt_list->t_mutex);
    i4_ret = u_datalist_head_enqueue(&pt_list->list_head, data, size, id);
    if (i4_ret)
    {
        MSGLIST_ERR("datalist enqueue failed!\n");
        pthread_mutex_unlock(&pt_list->t_mutex);
        return MSGLIST_FAIL;
    }
    pt_list->data_count += size;
    pthread_cond_broadcast(&pt_list->t_cond);
    pthread_mutex_unlock(&pt_list->t_mutex);

    return MSGLIST_SUCCESS;
}

DATANODE_T *u_msglist_receive(MSGLIST_T *pt_list)
{
    DATANODE_T *pt_node = NULL;

    if (!pt_list)
    {
        MSGLIST_ERR("pt_list can't be NULL!\n");
        return NULL;
    }

    pthread_mutex_lock(&pt_list->t_mutex);
    while ((pt_node = u_datalist_dequeue(&pt_list->list_head)) == NULL)
    {
        pthread_cond_wait(&pt_list->t_cond, &pt_list->t_mutex);
    }
    pt_list->data_count -= pt_node->size;
    pthread_mutex_unlock(&pt_list->t_mutex);

    return pt_node;
}

DATANODE_T *u_msglist_receive_timeout(MSGLIST_T *pt_list, unsigned int time)
{
    int i4_ret;
    struct timespec abstime;
    DATANODE_T *pt_node = NULL;

    if (!pt_list)
    {
        MSGLIST_ERR("pt_list can't be NULL!\n");
        return NULL;
    }

    pthread_mutex_lock(&pt_list->t_mutex);
    while ((pt_node = u_datalist_dequeue(&pt_list->list_head)) == NULL)
    {
        i4_ret = _msglist_transfer_time(&abstime, time);
        if (i4_ret)
        {
            pthread_mutex_unlock(&pt_list->t_mutex);
            return NULL;
        }

        i4_ret = pthread_cond_timedwait(&pt_list->t_cond, &pt_list->t_mutex, &abstime);
        if (i4_ret)
        {
            pthread_mutex_unlock(&pt_list->t_mutex);
            return NULL;
        }
    }
    pt_list->data_count -= pt_node->size;
    pthread_mutex_unlock(&pt_list->t_mutex);

    return pt_node;
}

unsigned int u_msglist_datacount(MSGLIST_T *pt_list)
{
    unsigned int count;
    if (!pt_list)
    {
        MSGLIST_ERR("pt_list can't be NULL!\n");
        return;
    }

    pthread_mutex_lock(&pt_list->t_mutex);
    count = pt_list->data_count;
    pthread_mutex_unlock(&pt_list->t_mutex);
    return count;
}

void u_msglist_flush(MSGLIST_T *pt_list)
{
    if (!pt_list)
    {
        MSGLIST_ERR("pt_list can't be NULL!\n");
        return;
    }

    pthread_mutex_lock(&pt_list->t_mutex);
    u_datalist_destroy(&pt_list->list_head);
    pt_list->data_count = 0;
    pthread_mutex_unlock(&pt_list->t_mutex);
}

void u_msglist_destroy(MSGLIST_T **ppt_list)
{
    if (!ppt_list || !(*ppt_list))
    {
        return;
    }
    MSGLIST_T *pt_list = *ppt_list;
    u_datalist_destroy(&pt_list->list_head);
    pthread_mutex_destroy(&pt_list->t_mutex);
    pthread_cond_destroy(&pt_list->t_cond);
    free(pt_list);
    *ppt_list = NULL;
}
