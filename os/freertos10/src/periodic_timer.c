
#include <termina.h>

#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/freertos10/name.h>
#include <termina/os/freertos10/time.h>

#include <FreeRTOS.h>

#include "timers.h"

typedef struct {

	void * handler;

	TimerHandle_t xTimer;

} __freertos_periodic_timer_t;


__freertos_periodic_timer_t __freertos_periodic_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

static inline __freertos_periodic_timer_t * __freertos_timer__get_timer(const __termina_id_t timer_id) {
	return &__freertos_periodic_timers[timer_id];
}

/**
 * \brief Array used to generate the names of the timers that are created.
 */

static char ntimer_name[5]  = "0000";

static void __freertos_timer__task_connection_handler(TimerHandle_t xTimer) {

	__termina_shared_periodic_timer_t * timer = (__termina_shared_periodic_timer_t *)pvTimerGetTimerID(xTimer);

	int32_t status = 0;

	__termina_event_t event = {
			.emitter_id = timer->emitter_id,
			.owner.type = __termina_active_entity__task,
			.owner.task.task_id = timer->connection.task.task_id,
			.port_id = timer->connection.task.sink_port_id
	};

	// Send a message to the task
	TickType_t current_ticks = xTaskGetTickCount();
	TimeVal current_time = __freertos_ticks_to_timeval(current_ticks);

	__termina_msg_queue__send(timer->connection.task.sink_msgq_id,
	                          &current_time, &status);
	__termina_msg_queue__send(timer->connection.task.task_msg_queue_id,
			&event, &status);
	// TODO: Check return status


}

static void __freertos_timer__handler_connection_handler(TimerHandle_t xTimer) {

	__termina_shared_periodic_timer_t * timer = (__termina_shared_periodic_timer_t *)pvTimerGetTimerID(xTimer);

	__status_int32_t ret;
	ret.__variant = Success;

	__termina_event_t event = {
			.emitter_id = timer->emitter_id,
			.owner.type = __termina_active_entity__handler,
			.owner.handler.handler_id = timer->connection.handler.handler_id,
			.port_id = 0 // The handler only has one sink port, so we set it to 0
	};

	TickType_t current_ticks = xTaskGetTickCount();
	TimeVal current_time = __freertos_ticks_to_timeval(current_ticks);

	// Aqui se puede usar xTaskGetTickCount() porque el callback no se ejecuta en el contexto de una ISR
	ret = timer->connection.handler.handler_action(&event,
	                                               timer->connection.handler.handler_object,
												   current_time); //TODO: Current_time

	if (Success != ret.__variant) {

		__termina_exec__reboot();

	}

}



void __termina_periodic_timer_os__init(const __termina_id_t timer_id,
		int32_t *const status) {

	__termina_shared_periodic_timer_t * timer = __termina_shared_timer__get_timer(timer_id);
	__freertos_periodic_timer_t * freertos_timer = __freertos_timer__get_timer(timer_id);

	*status = 0;

	// Install handler depending on the connection type
	if (__termina_emitter_connection_type__handler == timer->connection.type) {

		freertos_timer->handler = __freertos_timer__handler_connection_handler;

	} else {

		freertos_timer->handler = __freertos_timer__task_connection_handler;

	}

	NEXT_OBJECT_NAME(ntimer_name[0], ntimer_name[1], ntimer_name[2],
			ntimer_name[3]);

	const TickType_t xTimerPeriodInTicks = __freertos_timeval_to_ticks(timer->period);

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

