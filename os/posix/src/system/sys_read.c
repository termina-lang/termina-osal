
/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Read operation of the POSIX emulation, over the standard input.
 */

#include <termina.h>
#include <termina/shared/system/sys_read.h>
#include <unistd.h>


void termina__os__sys_read__read(char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], size_t * const read_bytes) {

    // The standard input is non-blocking, so the read returns at once when no
    // data is available.

    ssize_t result = read(STDIN_FILENO, str, TERMINA__SYS_READ__INPUT_BUFFER_SIZE);

    if (result < 0) {
        *read_bytes = 0;
    } else {
        *read_bytes = (size_t) result;
    }

    return;

}