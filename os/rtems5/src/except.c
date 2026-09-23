#include <termina.h>
#include <termina/shared/except.h>

#include <rtems.h>

void termina__os__except__init_emitter(void) {
    
    // Nothing to do for RTEMS
    return;
    
}

void termina__os__except__enter(void) {

    rtems_interrupt_level level;

    // On a single processor this stops preemption as well, since dispatch
    // happens on interrupt exit. The level is not restored, because the
    // exception path ends in a reset.
    rtems_interrupt_local_disable(level);
    (void) level;

}
