
#include <termina.h>
#include <termina/shared/system/sys_read.h>

void SystemEntry__read(const __termina_event_t * const __ev,
                       char str[__TERMINA_SYS_READ_INPUT_BUFFER_SIZE], size_t * const read_bytes) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_system_entry__read(str, read_bytes);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}
