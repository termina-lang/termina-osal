#ifndef __TERMINA__SHARED__SYSTEM__SYS_TIME_H__
#define __TERMINA__SHARED__SYSTEM__SYS_TIME_H__

#include <termina.h>

/**
 * \brief Returns the current uptime.
 *
 * @param[out] uptime   the current uptime.
 *
 */
void __termina_sys_time__clock_get_uptime(TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * @param[in] time_val  the blocking time.
 *
 */
void __termina_sys_time__delay_in(const TimeVal * const time_val);

void __termina_sys_time__clock_get_uptime_mutex(TimeVal * const uptime);
void __termina_sys_time__delay_in_mutex(const TimeVal * const time_val);

void __termina_sys_time__clock_get_uptime_task_lock(TimeVal * const uptime);
void __termina_sys_time__delay_in_task_lock(const TimeVal * const time_val);

void __termina_sys_time__clock_get_uptime_event_lock(TimeVal * const uptime);
void __termina_sys_time__delay_in_event_lock(const TimeVal * const time_val);

#endif // __TERMINA__SHARED__SYSTEM__SYS_TIME_H__