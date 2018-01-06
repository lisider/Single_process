#include "u_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CONTROL_INFO(...)

#define CONTROL_ERR(...) \
    do \
    { \
        printf("<CONTROL>[%s:%d]:", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__); \
    } \
    while (0)

typedef struct {
    pthread_mutex_t mMutex;
    pthread_cond_t mCond;
} CONTROL_T;

CONTROL_H u_control_init() {
    int ret;
    pthread_condattr_t condattr;

    CONTROL_T *handle = (CONTROL_T *)malloc(sizeof(CONTROL_T));
    if (NULL == handle) {
        CONTROL_ERR("CONTROL_T malloc failed!\n");
        goto MALLOC_ERR;
    }

    ret = pthread_mutex_init(&handle->mMutex, NULL);
    if (ret) {
        CONTROL_ERR("mutex init failed!\n");
        goto MUTEX_ERR;
    }

    ret = pthread_condattr_init(&condattr);
    if (ret) {
        CONTROL_ERR("condattr init failed!\n");
        goto ATTR_INIT_ERR;
    }

    ret = pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC);
    if (ret) {
        CONTROL_ERR("condattr setclock failed!\n");
        goto ATTR_INIT_ERR;
    }

    ret = pthread_cond_init(&handle->mCond, &condattr);
    if (ret) {
        CONTROL_ERR("cond init failed!\n");
        goto ATTR_INIT_ERR;
    }

    return handle;
ATTR_INIT_ERR:
    pthread_mutex_destroy(&handle->mMutex);
MUTEX_ERR:
    free(handle);
MALLOC_ERR:
    return NULL;
}

void u_control_deinit(CONTROL_H arg) {
    CONTROL_T *handle = (CONTROL_T *)arg;
    if (NULL == arg) {
        CONTROL_ERR("handle can't be NULL!\n");
        return;
    }
    pthread_mutex_destroy(&handle->mMutex);
    pthread_cond_destroy(&handle->mCond);
    free(handle);
}

void u_control_pause(CONTROL_H arg) {
    CONTROL_T *handle = (CONTROL_T *)arg;
    if (NULL == arg) {
        CONTROL_ERR("handle can't be NULL!\n");
        return;
    }
    pthread_mutex_lock(&handle->mMutex);
    pthread_cond_wait(&handle->mCond, &handle->mMutex);
    pthread_mutex_unlock(&handle->mMutex);
}

void u_control_resume(CONTROL_H arg) {
    CONTROL_T *handle = (CONTROL_T *)arg;
    if (NULL == arg) {
        CONTROL_ERR("handle can't be NULL!\n");
        return;
    }
    pthread_mutex_lock(&handle->mMutex);
    pthread_cond_broadcast(&handle->mCond);
    pthread_mutex_unlock(&handle->mMutex);
}

