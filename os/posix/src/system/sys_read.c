
#include <termina.h>
#include <termina/shared/system/sys_read.h>
#include <unistd.h>


void __termina_os_system_entry__read(const size_t size, char str[size], size_t * const read_bytes) {

    // Perform a non-blocking read from STDIN
    // The read syscall will return immediately if there is no data available

    ssize_t result = read(STDIN_FILENO, str, size);

    if (result < 0) {
        *read_bytes = 0;
    } else {
        *read_bytes = (size_t) result;
    }

    return;

}