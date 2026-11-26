/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Read operation, which each operating system implements.
 */

#ifndef TERMINA__SHARED__SYSTEM__SYS_READ_H__
#define TERMINA__SHARED__SYSTEM__SYS_READ_H__

#include <termina.h>

/**
 * @brief Reads characters from the input.
 *
 * @param[out] str         Array that receives the characters read.
 * @param[out] read_bytes  Number of characters read.
 */
extern void termina__os__sys_read__read(char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], 
                                            size_t * const read_bytes);


#endif // TERMINA__SHARED__SYSTEM__SYS_READ_H__
