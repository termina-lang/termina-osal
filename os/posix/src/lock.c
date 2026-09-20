
#include <termina.h>

#include <termina/shared/lock.h>
#include <termina/os/posix/signal.h>
    

termina__lock_t termina__os__irq_lock(void) {

    __posix_signal__disable();

    return 0;

}

void termina__os__irq_unlock(termina__lock_t irq_lock) {

    (void)irq_lock;

    __posix_signal__enable();

}
