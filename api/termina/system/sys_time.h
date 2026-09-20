#ifndef TERMINA__SYSTEM__SYS_TIME_H__
#define TERMINA__SYSTEM__SYS_TIME_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * \brief Returns the time elapsed since boot.
 *
 * @param[in]  termina__ev        the event that is being processed when the print is requested.
 * @param[out] uptime      the amount of elapsed time since boot.
 */
extern void SystemEntry__clock_get_uptime(const termina__event_t * const termina__ev,
                                          TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * @param[in] termina__ev        the event that is being processed when the print is requested.
 * @param[in] uptime      the amount of time that the task will be blocked.
 */
extern void SystemEntry__delay_in(const termina__event_t * termina__ev,
                                  const TimeVal * const uptime);

#endif // TERMINA__SYSTEM__SYS_TIME_H__
