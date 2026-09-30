
#ifndef TERMINA__OS__FREERTOS10__TIME_H__
#define TERMINA__OS__FREERTOS10__TIME_H__

#include <termina.h>

#include <FreeRTOS.h>

TickType_t termina__freertos__timeval_to_ticks(TimeVal period);

TimeVal termina__freertos__ticks_to_timeval(uint64_t ticks);

/**
 * \brief Returns the ticks elapsed since the scheduler started, in 64 bits.
 *
 * The tick count of the kernel is a TickType_t and wraps around; the number of
 * times it has done so, which the kernel keeps, extends it to 64 bits.
 * Callable from a task and from an interrupt.
 */
uint64_t termina__freertos__uptime_ticks(void);

/**
 * \brief Reads the tick count of the kernel and the number of times it has
 * wrapped around, together.
 *
 * Defined in freertos_tasks_c_additions.h, which tasks.c includes, since both
 * are static to tasks.c.
 */
void termina__freertos__read_tick_count(BaseType_t * const overflows,
                                        TickType_t * const ticks);

#endif // TERMINA__OS__FREERTOS10__TIME_H__