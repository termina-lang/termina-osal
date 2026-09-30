
#include <termina/os/freertos10/time.h>
#include <termina/shared/time.h>

#include <FreeRTOS.h>
#include "timers.h"

uint64_t termina__freertos__uptime_ticks(void){

	BaseType_t overflows = 0;
	TickType_t ticks = 0U;

	termina__freertos__read_tick_count(&overflows, &ticks);

	return ((uint64_t)(UBaseType_t)overflows << (8U * sizeof(TickType_t)))
	       + (uint64_t)ticks;
}

TickType_t termina__freertos__timeval_to_ticks(TimeVal period){

	TickType_t ticks_per_period = 0;

	ticks_per_period += (TickType_t)((period.tv_sec) * (termina__shared__time__ticks_per_sec()));
	ticks_per_period += (period.tv_usec) / TERMINA__TIME__MICROSECONDS_PER_TICK;

	return ticks_per_period;
}

TimeVal termina__freertos__ticks_to_timeval(uint64_t ticks){

	TimeVal start_time;

	uint64_t microseconds = ticks * TERMINA__TIME__MICROSECONDS_PER_TICK;

	start_time.tv_sec = (uint32_t)(microseconds / 1000000U);
	start_time.tv_usec = (uint32_t)(microseconds % 1000000U);

	return start_time;
}

