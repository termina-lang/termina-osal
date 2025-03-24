
#include <termina.h>

#include <rtems.h>

__termina_task_lock_t __termina_task__lock(void) {

    rtems_interrupt_level level;

    rtems_interrupt_disable(level);

    return level;

}

void __termina_task__unlock(__termina_task_lock_t lock) {

    rtems_interrupt_enable(lock);

}

__termina_event_lock_t __termina_event__lock(void) {

    rtems_interrupt_level level;

    rtems_interrupt_disable(level);

    return level;

}

void __termina_event__unlock(__termina_event_lock_t lock) {

    rtems_interrupt_enable(lock);

}