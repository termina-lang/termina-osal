#ifndef __TERMINA__SHARED__SYSTEM__SYS_READ_H__
#define __TERMINA__SHARED__SYSTEM__SYS_READ_H__

#include <termina.h>

/**
 * \brief Read a string.
 *
 * @param[in]  size        the size of the read buffer.
 * @param[in]  str         the array that will store the read characters.
 * @param[out] read_bytes  the number of characters effectively read. 
 */
extern void __termina_os_system_entry__read(const size_t size, 
                                            char str[size], size_t * const read_bytes);


#endif // __TERMINA__SHARED__SYSTEM__SYS_READ_H__
