
#include <termina.h>
#include <termina/shared/lock.h>

#include <FreeRTOS.h>
#include "task.h"


__termina_lock_t __termina_os__irq_lock(void) {

	__termina_lock_t lock = 0;

    if (xPortIsInsideInterrupt()) {

        // Lock interrupts from a handler
		lock = taskENTER_CRITICAL_FROM_ISR();

    } else {

        // Lock interrupts from a task
		taskENTER_CRITICAL();
		
    }

    return lock;

}

void __termina_os__irq_unlock(__termina_lock_t irq_lock) {


    if (xPortIsInsideInterrupt()) {

        // Unlock interrupts from a handler
		taskEXIT_CRITICAL_FROM_ISR(irq_lock);

    } else {

        // Unlock interrupts from a task
		taskEXIT_CRITICAL();

    } 

    return;

}
