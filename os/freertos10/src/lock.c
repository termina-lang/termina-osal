
#include <termina.h>
#include <termina/shared/lock.h>

#include <FreeRTOS.h>
#include "task.h"


__termina_lock_t __termina_os_task__irq_lock(void) {

	taskENTER_CRITICAL();

    return 0;

}

void __termina_os_task__irq_unlock(__termina_lock_t lock) {

    (void)lock;

	taskEXIT_CRITICAL();

}

__termina_lock_t __termina_os_handler__irq_lock(void) {

	return taskENTER_CRITICAL_FROM_ISR();


}

void __termina_os_handler__irq_unlock(__termina_lock_t lock) {

	taskEXIT_CRITICAL_FROM_ISR(lock);

}

__termina_lock_t __termina_os_timer__irq_lock(void) {

	return taskENTER_CRITICAL_FROM_ISR();

}

void __termina_os_timer__irq_unlock(__termina_lock_t lock) {

	taskEXIT_CRITICAL_FROM_ISR(lock);

}