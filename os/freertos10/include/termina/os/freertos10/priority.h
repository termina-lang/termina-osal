#ifndef TERMINA__OS__FREERTOS10__PRIORITY_H__
#define TERMINA__OS__FREERTOS10__PRIORITY_H__

#include <termina.h>

#include <FreeRTOS.h>

/* Priority inversion between Termina (0 = highest) and FreeRTOS
   (configMAX_PRIORITIES - 1 = highest). Application tasks use 1 to 254. */
static inline UBaseType_t termina__freertos__task__priority_to_freertos(termina__task_prio_t priority) {

	return (UBaseType_t) (configMAX_PRIORITIES - 1U) - (UBaseType_t) priority;

}

#endif // TERMINA__OS__FREERTOS10__PRIORITY_H__