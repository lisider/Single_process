#ifndef __U_RINGBUF_H__
#define __U_RINGBUF_H__

#include "u_common.h"

typedef enum
{
    RINGBUF_INV_ARG = -1,
    RINGBUF_OK = 0,
} RINGBUF_RES_E;

typedef void *RINGBUF_H;

extern RINGBUF_H u_ringbuf_malloc(UINT32 ui4_size);
extern VOID u_ringbuf_free(RINGBUF_H handle);
extern INT32 u_ringbuf_write(RINGBUF_H handle, void *p_data, UINT32 ui4_size);
extern INT32 u_ringbuf_read(RINGBUF_H handle, void *p_buf, UINT32 ui4_size);
extern INT32 u_ringbuf_clear(RINGBUF_H handle);
extern INT32 u_ringbuf_get_used_size(RINGBUF_H handle);

#endif
