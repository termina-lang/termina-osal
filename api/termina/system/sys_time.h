#ifndef __TERMINA__SYSTEM__SYS_TIME_H__
#define __TERMINA__SYSTEM__SYS_TIME_H__

#include <termina/types.h>
#include <termina/prelude.h>

extern void System__clock_get_uptime(TimeVal * const uptime);
extern void System__delay_in(const TimeVal * const uptime);

#endif // __TERMINA__SYSTEM__SYS_TIME_H__
