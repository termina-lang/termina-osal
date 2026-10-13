#include <termina.h>
#include <termina/shared/exec.h>

#include <rtems.h>

void termina__os__exec__quiesce(void) {

    rtems_interrupt_level level;

    // On a single processor this stops preemption as well, since dispatch
    // happens on interrupt exit. The level is not restored, because both the
    // exception path and a handover never come back.
    rtems_interrupt_local_disable(level);
    (void) level;

}
