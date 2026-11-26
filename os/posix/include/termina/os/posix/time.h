/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Time services of the POSIX emulation: tick, active timers and
 *        delayed tasks.
 */

#ifndef TERMINA__OS__POSIX__TIMER_H__
#define TERMINA__OS__POSIX__TIMER_H__

#include <termina.h>

#include <termina/shared/list/list.h>

/**
 * @brief List of the active timers.
 */
extern termina__shared__list_t termina__posix__timers_list;

/**
 * @brief List of the tasks blocked until a delay expires.
 */
extern termina__shared__list_t termina__posix__delayed_tasks_list;

/**
 * @brief Initializes the time services.
 */
void termina__posix__time__init(void);

/**
 * @brief Handler of the tick signal.
 *
 * The tick task, which periodically sends a signal to the current task,
 * generates the tick signal.
 *
 * @param[in] signum  Number of the signal received.
 */
void termina__posix__time__tick_handler(int signum);

/**
 * @brief Gets the current time.
 * 
 * @param[out] current_time  Current time.
 */
void termina__posix__time__get_current_time(TimeVal * const current_time);

#endif // TERMINA__OS__POSIX__TIMER_H__
