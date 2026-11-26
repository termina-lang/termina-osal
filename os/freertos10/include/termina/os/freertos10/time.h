/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Conversion between time values and FreeRTOS ticks, and uptime in
 *        ticks.
 */

#ifndef TERMINA__OS__FREERTOS10__TIME_H__
#define TERMINA__OS__FREERTOS10__TIME_H__

#include <termina.h>

#include <FreeRTOS.h>

/**
 * @brief Converts a time value to FreeRTOS ticks.
 *
 * @param[in] period  Time value to convert.
 *
 * @return The number of ticks.
 */
TickType_t termina__freertos__timeval_to_ticks(TimeVal period);

/**
 * @brief Converts a number of FreeRTOS ticks to a time value.
 *
 * @param[in] ticks  Number of ticks.
 *
 * @return The time value.
 */
TimeVal termina__freertos__ticks_to_timeval(uint64_t ticks);

/**
 * @brief Gets the ticks elapsed since the scheduler started, in 64 bits.
 *
 * The tick count of the kernel is a `TickType_t` and wraps around; the number
 * of times it has done so, which the kernel keeps, extends it to 64 bits. The
 * function can be called from a task and from an interrupt.
 *
 * @return The number of ticks since the scheduler started.
 */
uint64_t termina__freertos__uptime_ticks(void);

/**
 * @brief Reads the tick count of the kernel and the number of times it has
 *        wrapped around, together.
 *
 * The function is defined in `freertos_tasks_c_additions.h`, which `tasks.c`
 * includes, since both values are static to `tasks.c`.
 *
 * @param[out] overflows  Number of times the tick count has wrapped around.
 * @param[out] ticks      Tick count of the kernel.
 */
void termina__freertos__read_tick_count(BaseType_t * const overflows,
                                        TickType_t * const ticks);

#endif // TERMINA__OS__FREERTOS10__TIME_H__