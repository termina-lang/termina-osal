#ifndef __TERMINA__OS__FREERTOS10__PRIORITY_H__
#define __TERMINA__OS__FREERTOS10__PRIORITY_H__

#include <termina.h>

#include <FreeRTOS.h>

static inline UBaseType_t __termina_os_task__priority2freertos(__termina_task_prio_t priority) {

	UBaseType_t freertos_priority = 255-priority;
	return freertos_priority;

}

#endif // __TERMINA__OS__FREERTOS10__PRIORITY_H__