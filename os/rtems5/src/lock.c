
#include <termina.h>
#include <termina/shared/lock.h>

#include <rtems.h>

__termina_lock_t __termina_os_task__irq_lock(void) {

    rtems_interrupt_level level;

    rtems_interrupt_disable(level);

    return level;

}

void __termina_os_task__irq_unlock(__termina_lock_t lock) {

    rtems_interrupt_enable(lock);

}

__termina_lock_t __termina_os_handler__irq_lock(void) {

    rtems_interrupt_level level;

    rtems_interrupt_disable(level);

    return level;

}

void __termina_os_handler__irq_unlock(__termina_lock_t lock) {

    rtems_interrupt_enable(lock);

}