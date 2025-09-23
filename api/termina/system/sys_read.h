#ifndef __TERMINA__SYSTEM__SYS_READ_H__
#define __TERMINA__SYSTEM__SYS_READ_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * \brief Print a string.
 *
 * @param[in]  __ev        the event that is being processed when the print is requested.
 * @param[in]  size        the size of the array that will store the read characters.
 * @param[in]  str         the array that will store the read characters.
 * @param[out] read_bytes  the number of characters effectively read.
 */
extern void SystemEntry__read(const __termina_event_t * const __ev,
                              const size_t size, char str[size], size_t * const read_bytes);


#endif // __TERMINA__SYSTEM__SYS_READ_H__
