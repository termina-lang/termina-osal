#ifndef __TERMINA__SHARED__SYSTEM__SYS_TIME_H__
#define __TERMINA__SHARED__SYSTEM__SYS_TIME_H__

#include <termina.h>

/**
 * \brief Returns the current uptime.
 *
 * @param[out] uptime   the current uptime.
 *
 */
void SystemEntry__clock_get_uptime(TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * @param[in] time_val  the blocking time.
 *
 */
void SystemEntry__delay_in(const TimeVal * const time_val);

#endif // __TERMINA__SHARED__SYSTEM__SYS_TIME_H__