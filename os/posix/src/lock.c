
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

    // Handlers are uninterruptible in POSIX.
    return 0;

}

void __termina_os_handler__irq_unlock(__termina_lock_t lock) {

    // Handlers are uninterruptible in POSIX.
    (void)lock;
    return;

}

__termina_lock_t __termina_os_timer__irq_lock(void) {

    // In POSIX, timers are executed in the context of the
    // signal handler, which is uninterruptible.

    return 0;

}

void __termina_os_timer__irq_unlock(__termina_lock_t lock) {

    // In POSIX, timers are executed in the context of the
    // signal handler, which is uninterruptible.
    (void)lock;
    return;

}