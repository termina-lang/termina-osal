
#include <termina.h>
#include <termina/shared/lock.h>

#include <FreeRTOS.h>
#include "task.h"

// Interrupt mask saved by the holder of each lock when it runs in a handler;
// a task needs none, since FreeRTOS keeps its own nesting count
static UBaseType_t termina__freertos__irq_lock_mask[TERMINA__SHARED__IRQ_LOCK_TABLE_SIZE];

void termina__os__irq_lock(const termina__id_t lock_id) {

    if (xPortIsInsideInterrupt()) {

        // Lock interrupts from a handler
		termina__freertos__irq_lock_mask[lock_id] = taskENTER_CRITICAL_FROM_ISR();

    } else {

        // Lock interrupts from a task
		taskENTER_CRITICAL();

    }

}

void termina__os__irq_unlock(const termina__id_t lock_id) {

    if (xPortIsInsideInterrupt()) {

        // Unlock interrupts from a handler
		taskEXIT_CRITICAL_FROM_ISR(termina__freertos__irq_lock_mask[lock_id]);

    } else {

        // Unlock interrupts from a task
		taskEXIT_CRITICAL();

    }

    return;

}
