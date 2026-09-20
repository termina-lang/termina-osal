#ifndef TERMINA__SHARED__SYSTEM__SYS_TIME_H__
#define TERMINA__SHARED__SYSTEM__SYS_TIME_H__

#include <termina/types.h>
#include <termina/prelude.h>


/**
 * \brief Returns the time elapsed since boot.
 *
 * @param[out] uptime      the amount of elapsed time since boot.
 */
extern void termina__os__sys_time__clock_get_uptime(TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * @param[in] uptime      the amount of time that the task will be blocked.
 */
extern void termina__os__sys_time__delay_in(const TimeVal * const uptime);

#endif // TERMINA__SHARED__SYSTEM__SYS_TIME_H__
