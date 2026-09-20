
#include <termina.h>
#include <termina/shared/system/sys_read.h>

void SystemEntry__read(const termina__event_t * const termina__ev,
                       char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], size_t * const read_bytes) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os__sys_read__read(str, read_bytes);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}
