
#ifndef __TERMINA__OS__FREERTOS10__TIME_H__
#define __TERMINA__OS__FREERTOS10__TIME_H__

#include <termina.h>

#include <FreeRTOS.h>

TickType_t __freertos_timeval_to_ticks(TimeVal period);

TimeVal __freertos_ticks_to_timeval(TickType_t ticks);

#endif // __TERMINA__OS__FREERTOS10__TIME_H__