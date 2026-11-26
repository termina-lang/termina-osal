/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Read procedure of the system entry.
 */

#ifndef TERMINA__SYSTEM__SYS_READ_H__
#define TERMINA__SYSTEM__SYS_READ_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * @brief Size of the input buffer, 256 characters unless the build defines
 *        it.
 */
#ifndef TERMINA__SYS_READ__INPUT_BUFFER_SIZE
#define TERMINA__SYS_READ__INPUT_BUFFER_SIZE 256
#endif

/**
 * @brief Reads characters from the input.
 *
 * @param[in]  termina__ev    Pointer to the event that is being processed.
 * @param[in]  termina__this  Pointer to the system entry object.
 * @param[out] str            Array that receives the characters read.
 * @param[out] read_bytes     Number of characters read.
 */
extern void SystemEntry__read(const termina__event_t * const termina__ev,
                              void * const termina__this,
                              char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], size_t * const read_bytes);


#endif // TERMINA__SYSTEM__SYS_READ_H__
