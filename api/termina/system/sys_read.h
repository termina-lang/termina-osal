#ifndef __TERMINA__SYSTEM__SYS_READ_H__
#define __TERMINA__SYSTEM__SYS_READ_H__

#include <termina/types.h>
#include <termina/prelude.h>

#include "config.h"

/**
 * \brief Size of the input buffer. If not specified, the default value
 *        of 256 characters is used.
 */
#ifndef __TERMINA_SYS_READ_INPUT_BUFFER_SIZE
#define __TERMINA_SYS_READ_INPUT_BUFFER_SIZE 256
#endif

/**
 * \brief Print a string.
 *
 * @param[in]  __ev        the event that is being processed when the print is requested.
 * @param[in]  str         the array that will store the read characters.
 * @param[out] read_bytes  the number of characters effectively read.
 */
extern void SystemEntry__read(const __termina_event_t * const __ev,
                              char str[__TERMINA_SYS_READ_INPUT_BUFFER_SIZE], size_t * const read_bytes);


#endif // __TERMINA__SYSTEM__SYS_READ_H__
