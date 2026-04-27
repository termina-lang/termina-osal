    
#include <termina.h>
#include <termina/shared/lock.h>

#include <rtems.h>

__termina_lock_t __termina_os__irq_lock(void) {

    rtems_interrupt_level level;

    rtems_interrupt_disable(level);

    return level;

}

void __termina_os__irq_unlock(__termina_lock_t irq_lock) {

    rtems_interrupt_enable(irq_lock);

}
