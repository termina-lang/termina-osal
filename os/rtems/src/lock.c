    
#include <termina.h>
#include <termina/shared/lock.h>

#include <rtems.h>

termina__lock_t termina__os__irq_lock(void) {

    rtems_interrupt_level level;

    rtems_interrupt_disable(level);

    return level;

}

void termina__os__irq_unlock(termina__lock_t irq_lock) {

    rtems_interrupt_enable(irq_lock);

}
