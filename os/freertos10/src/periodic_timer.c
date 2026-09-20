
#include <termina.h>

#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/freertos10/name.h>
#include <termina/os/freertos10/time.h>

#include <FreeRTOS.h>

#include "timers.h"

typedef struct {

	TimerCallbackFunction_t handler;

	TimerHandle_t xTimer;

} termina__freertos__periodic_timer_t;


termina__freertos__periodic_timer_t termina__freertos__periodic_timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

static inline termina__freertos__periodic_timer_t * termina__freertos__timer__get_timer(const termina__id_t timer_id) {
	return &termina__freertos__periodic_timers[timer_id];
}

/**
 * \brief Array used to generate the names of the timers that are created.
 */

static char ntimer_name[5]  = "0000";

static void termina__freertos__timer__task_connection_handler(TimerHandle_t xTimer) {

	termina__shared__periodic_timer_t * timer = (termina__shared__periodic_timer_t *)pvTimerGetTimerID(xTimer);

	int32_t status = 0;

	termina__event_t event = {
			.emitter_id = timer->emitter_id,
			.owner.type = termina__active_entity__task,
			.owner.task.task_id = timer->connection.task.task_id,
			.port_id = timer->connection.task.sink_port_id
	};

	// Send a message to the task
	TickType_t current_ticks = xTaskGetTickCount();
	TimeVal current_time = termina__freertos__ticks_to_timeval(current_ticks);

	termina__msg_queue__send(timer->connection.task.sink_msgq_id,
	                          &current_time, &status);
	termina__msg_queue__send(timer->connection.task.task_msg_queue_id,
			&event, &status);
	// TODO: Check return status


}

static void termina__freertos__timer__handler_connection_handler(TimerHandle_t xTimer) {

	termina__shared__periodic_timer_t * timer = (termina__shared__periodic_timer_t *)pvTimerGetTimerID(xTimer);

	Status__i32 ret;
	ret._variant = Status__Success;

	termina__event_t event = {
			.emitter_id = timer->emitter_id,
			.owner.type = termina__active_entity__handler,
			.owner.handler.handler_id = timer->connection.handler.handler_id,
			.port_id = 0 // The handler only has one sink port, so we set it to 0
	};

	TickType_t current_ticks = xTaskGetTickCount();
	TimeVal current_time = termina__freertos__ticks_to_timeval(current_ticks);

	// Aqui se puede usar xTaskGetTickCount() porque el callback no se ejecuta en el contexto de una ISR
	ret = timer->connection.handler.handler_action(&event,
	                                               timer->connection.handler.handler_object,
												   current_time); //TODO: Current_time

	if (Status__Success != ret._variant) {

		termina__exec__reboot();

	}

}



void termina__periodic_timer_os__init(const termina__id_t timer_id,
		int32_t *const status) {

	termina__shared__periodic_timer_t * timer = termina__shared__timer__get_timer(timer_id);
	termina__freertos__periodic_timer_t * freertos_timer = termina__freertos__timer__get_timer(timer_id);

	*status = 0;

	// Install handler depending on the connection type
	if (termina__emitter_connection_type__handler == timer->connection.type) {

		freertos_timer->handler = termina__freertos__timer__handler_connection_handler;

	} else {

		freertos_timer->handler = termina__freertos__timer__task_connection_handler;

	}

	NEXT_OBJECT_NAME(ntimer_name[0], ntimer_name[1], ntimer_name[2],
			ntimer_name[3]);

	const TickType_t xTimerPeriodInTicks = termina__freertos__timeval_to_ticks(timer->period);

	freertos_timer->xTimer = xTimerCreate(ntimer_name, 
			xTimerPeriodInTicks,
			pdTRUE, // auto-reload
			(void *)timer,
			freertos_timer->handler );

	if (NULL != freertos_timer->xTimer) {

		if(xTimerStart(freertos_timer->xTimer, 0) != pdPASS){

			*status = -1;

		}

	}

	return;

}

