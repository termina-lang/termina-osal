
#include <termina.h>
#include <termina/shared/system/sys_read.h>
#include <unistd.h>


void termina__os_sys_read__read(char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], size_t * const read_bytes) {

    // Perform a non-blocking read from STDIN
    // The read syscall will return immediately if there is no data available

    ssize_t result = read(STDIN_FILENO, str, TERMINA__SYS_READ__INPUT_BUFFER_SIZE);

    if (result < 0) {
        *read_bytes = 0;
    } else {
        *read_bytes = (size_t) result;
    }

    return;

}