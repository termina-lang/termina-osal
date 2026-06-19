#ifndef __TERMINA__SHARED__SYSTEM__SYS_READ_H__
#define __TERMINA__SHARED__SYSTEM__SYS_READ_H__

#include <termina.h>

/**
 * \brief Read a string.
 *
 * @param[in]  str         the array that will store the read characters.
 * @param[out] read_bytes  the number of characters effectively read. 
 */
extern void __termina_os_system_entry__read(char str[__TERMINA_SYS_READ_INPUT_BUFFER_SIZE], 
                                            size_t * const read_bytes);


#endif // __TERMINA__SHARED__SYSTEM__SYS_READ_H__
