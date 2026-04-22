
#include <termina.h>

#include <termina/shared/lock.h>
#include <termina/os/posix/signal.h>
    

__termina_lock_t __termina_os__irq_lock(const __termina_active_entity_t * const owner) {

    if (owner->type == __termina_active_entity__task) {
        __posix_signal__disable();
    } else {
        // Handlers are uninterruptible in POSIX.
        // Also, in POSIX, timers are executed in the context of the
        // signal handler.
    }

    return 0;

}

void __termina_os__irq_unlock(const __termina_active_entity_t * const owner,
                              __termina_lock_t irq_lock) {

    (void)irq_lock;
    if (owner->type == __termina_active_entity__task) {
        __posix_signal__enable();
    }  else {
        // Handlers are uninterruptible in POSIX.
        // Also, in POSIX, timers are executed in the context of the
        // signal handler.
    }

}
