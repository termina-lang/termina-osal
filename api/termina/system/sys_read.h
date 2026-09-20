#ifndef TERMINA__SYSTEM__SYS_READ_H__
#define TERMINA__SYSTEM__SYS_READ_H__

#include <termina/types.h>
#include <termina/prelude.h>

#include "config.h"

/**
 * \brief Size of the input buffer. If not specified, the default value
 *        of 256 characters is used.
 */
#ifndef TERMINA__SYS_READ__INPUT_BUFFER_SIZE
#define TERMINA__SYS_READ__INPUT_BUFFER_SIZE 256
#endif

/**
 * \brief Print a string.
 *
 * @param[in]  termina__ev        the event that is being processed when the print is requested.
 * @param[in]  str         the array that will store the read characters.
 * @param[out] read_bytes  the number of characters effectively read.
 */
extern void SystemEntry__read(const termina__event_t * const termina__ev,
                              char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], size_t * const read_bytes);


#endif // TERMINA__SYSTEM__SYS_READ_H__
