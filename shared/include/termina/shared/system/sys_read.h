#ifndef TERMINA__SHARED__SYSTEM__SYS_READ_H__
#define TERMINA__SHARED__SYSTEM__SYS_READ_H__

#include <termina.h>

/**
 * \brief Read a string.
 *
 * @param[in]  str         the array that will store the read characters.
 * @param[out] read_bytes  the number of characters effectively read. 
 */
extern void termina__os__sys_read__read(char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], 
                                            size_t * const read_bytes);


#endif // TERMINA__SHARED__SYSTEM__SYS_READ_H__
