#ifndef __TERMINA__SYSTEM__SYS_TIME_H__
#define __TERMINA__SYSTEM__SYS_TIME_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * \brief Returns the time elapsed since boot.
 *
 * @param[in]  __ev        the event that is being processed when the print is requested.
 * @param[out] uptime      the amount of elapsed time since boot.
 */
extern void SystemEntry__clock_get_uptime(const __termina_event_t * const __ev,
                                          TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * @param[in] __ev        the event that is being processed when the print is requested.
 * @param[in] uptime      the amount of time that the task will be blocked.
 */
extern void SystemEntry__delay_in(const __termina_event_t * __ev,
                                  const TimeVal * const uptime);

#endif // __TERMINA__SYSTEM__SYS_TIME_H__
