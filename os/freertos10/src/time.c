
#include <termina/os/freertos10/time.h>

#include <FreeRTOS.h>
#include "timers.h"

TickType_t __freertos_timeval_to_ticks(TimeVal period){

	TickType_t ticks_per_period = 0;

	ticks_per_period += (period.tv_sec)*(__termina__get_ticks_per_sec());
	ticks_per_period += (period.tv_usec) / __TERMINA_MICROSECONDS_PER_TICK;

	return ticks_per_period;
}

TimeVal __freertos_ticks_to_timeval(TickType_t ticks){

	TimeVal start_time;

	uint64_t microseconds = (uint64_t)ticks * __TERMINA_MICROSECONDS_PER_TICK;

	start_time.tv_sec = (uint32_t)(microseconds / 1000000U);
	start_time.tv_usec = (uint32_t)(microseconds % 1000000U);

	return start_time;
}

