
#include <termina.h>
#include <termina/shared/system/sys_read.h>

void SystemEntry__read(const termina__event_t * const termina__ev,
                       void * const termina__this,
                       char str[TERMINA__SYS_READ__INPUT_BUFFER_SIZE], size_t * const read_bytes) {

    termina__system_entry_t * self = (termina__system_entry_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    termina__os__sys_read__read(str, read_bytes);

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type,
                               termina__lock);

}
