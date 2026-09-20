
#ifndef TERMINA__OS__FREERTOS10__TIME_H__
#define TERMINA__OS__FREERTOS10__TIME_H__

#include <termina.h>

#include <FreeRTOS.h>

TickType_t termina__freertos__timeval_to_ticks(TimeVal period);

TimeVal termina__freertos__ticks_to_timeval(TickType_t ticks);

#endif // TERMINA__OS__FREERTOS10__TIME_H__