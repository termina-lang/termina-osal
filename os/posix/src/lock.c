
#include <termina.h>

#include <termina/shared/lock.h>
#include <termina/os/posix/signal.h>


void termina__os__irq_lock(const termina__id_t lock_id) {

    // One process: blocking the signals excludes every other user, and the
    // signal module keeps its own nesting count
    (void)lock_id;

    termina__posix__signal__disable();

}

void termina__os__irq_unlock(const termina__id_t lock_id) {

    (void)lock_id;

    termina__posix__signal__enable();

}
