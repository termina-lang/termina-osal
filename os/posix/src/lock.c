
#include <termina.h>

#include <termina/shared/lock.h>
#include <termina/os/posix/signal.h>

__termina_lock_t __termina_os_task__irq_lock(void) {

    __posix_signal__disable();

    return 0;

}

void __termina_os_task__irq_unlock(__termina_lock_t lock) {

    __posix_signal__enable();

}

__termina_lock_t __termina_os_handler__irq_lock(void) {

    __posix_signal__disable();

    return 0;

}

void __termina_os_handler__irq_unlock(__termina_lock_t lock) {

    __posix_signal__enable();

}