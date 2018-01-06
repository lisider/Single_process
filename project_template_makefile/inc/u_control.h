#ifndef __U_CONTROL_H__
#define __U_CONTROL_H__

typedef void* CONTROL_H;

extern CONTROL_H u_control_init();
extern void u_control_deinit(CONTROL_H handle);
extern void u_control_pause(CONTROL_H handle);
extern void u_control_resume(CONTROL_H handle);

#endif
