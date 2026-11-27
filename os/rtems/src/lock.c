
/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Interrupt locks on RTEMS.
 */

#include <termina.h>
#include <termina/shared/lock.h>

#include <rtems.h>

// Interrupt level saved by the holder of each lock
static rtems_interrupt_level termina__rtems__irq_lock_level[TERMINA__SHARED__IRQ_LOCK_TABLE_SIZE];

void termina__os__irq_lock(const termina__id_t lock_id) {

    rtems_interrupt_level level;

    // On a single processor, disabling the interrupts excludes every other
    // user of the lock.
    rtems_interrupt_local_disable(level);

    termina__rtems__irq_lock_level[lock_id] = level;

}

void termina__os__irq_unlock(const termina__id_t lock_id) {

    rtems_interrupt_local_enable(termina__rtems__irq_lock_level[lock_id]);

}
