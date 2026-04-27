
#include <termina.h>

#include <termina/shared/lock.h>
#include <termina/os/posix/signal.h>
    

__termina_lock_t __termina_os__irq_lock(void) {

    __posix_signal__disable();

    return 0;

}

void __termina_os__irq_unlock(__termina_lock_t irq_lock) {

    (void)irq_lock;

    __posix_signal__enable();

}
