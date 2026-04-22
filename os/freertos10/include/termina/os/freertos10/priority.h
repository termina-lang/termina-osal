#ifndef __TERMINA__OS__FREERTOS10__PRIORITY_H__
#define __TERMINA__OS__FREERTOS10__PRIORITY_H__

#include <termina.h>

#include <FreeRTOS.h>

/* Priority inversion between Termina (0 = highest) and FreeRTOS
   (configMAX_PRIORITIES - 1 = highest). Termina priority 0 is reserved for the
   runtime: it maps to the top FreeRTOS priority, which is used by the
   software-timer daemon task (configTIMER_TASK_PRIORITY). Application tasks
   must use Termina priorities strictly greater than 0. */
static inline UBaseType_t __termina_os_task__priority2freertos(__termina_task_prio_t priority) {

	return (UBaseType_t) (configMAX_PRIORITIES - 1U) - (UBaseType_t) priority;

}

#endif // __TERMINA__OS__FREERTOS10__PRIORITY_H__