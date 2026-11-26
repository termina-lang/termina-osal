/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Clock procedure of the system entry.
 */

#ifndef TERMINA__SYSTEM__SYS_TIME_H__
#define TERMINA__SYSTEM__SYS_TIME_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * @brief Gets the time elapsed since boot.
 *
 * @param[in]  termina__ev    Pointer to the event that is being processed.
 * @param[in]  termina__this  Pointer to the system entry object.
 * @param[out] uptime         Time elapsed since boot.
 */
extern void SystemEntry__clock_get_uptime(const termina__event_t * const termina__ev,
                                          const void * const termina__this,
                                          TimeVal * const uptime);

#endif // TERMINA__SYSTEM__SYS_TIME_H__
