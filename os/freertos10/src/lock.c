
#include <termina.h>
#include <termina/shared/lock.h>

#include <FreeRTOS.h>
#include "task.h"


__termina_lock_t __termina_os__irq_lock(const __termina_active_entity_t * const owner) {

	__termina_lock_t lock = 0;

    if (owner->type == __termina_active_entity__task) {

        // Lock interrupts from a task
		taskENTER_CRITICAL();

    } else if (owner->type == __termina_active_entity__handler) {

        // Lock interrupts from a handler
		lock = taskENTER_CRITICAL_FROM_ISR();

    } else {

        // Lock interrupts from a timer
		
		// In FreeRTOS, timers are executed in the context of the timer service
		// task, which is a normal task. Therefore, locking interrupts from a
		// timer is the same as locking interrupts from a task.

		taskENTER_CRITICAL();

    }

    return lock;

}

void __termina_os__irq_unlock(const __termina_active_entity_t * const owner,
                              __termina_lock_t irq_lock) {


    if (owner->type == __termina_active_entity__task) {

        // Unlock interrupts from a task
		taskEXIT_CRITICAL();

    } else if (owner->type == __termina_active_entity__handler) {

        // Unlock interrupts from a handler
		taskEXIT_CRITICAL_FROM_ISR(irq_lock);

    } else {

        // Unlock interrupts from a timer
		
		// In FreeRTOS, timers are executed in the context of the timer service
		// task, which is a normal task. Therefore, unlocking interrupts from a
		// timer is the same as unlocking interrupts from a task.

		taskEXIT_CRITICAL();

    }

}
