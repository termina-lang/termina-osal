
#include <termina.h>

#include <termina/shared/time.h>
#include <termina/shared/except.h>
#include <termina/shared/msg_queue.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/rtems/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_timer_id;

    rtems_timer_service_routine_entry handler;

    TimeVal next_time;

    } termina__rtems__periodic_timer_t;

static termina__rtems__periodic_timer_t termina__rtems__periodic_timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

static inline termina__rtems__periodic_timer_t * termina__rtems__timer__get_timer(const termina__id_t timer_id) {
    return &termina__rtems__periodic_timers[timer_id];
}

/**
 * \brief Array used to generate the names of the timers that are created.
 */
static int8_t ntimer_name[5]  = "0000";

/**
 * \brief Returns the number of ticks from now until next_time, rounded up.
 */
static rtems_interval get_sleep_time(const TimeVal * const next_time) {

    rtems_interval sleep_time = 1;

    struct timeval current_time;
    current_time.tv_sec = 0;
    current_time.tv_usec = 0;

    rtems_clock_get_uptime_timeval(&current_time);

    const uint64_t next_us = ((uint64_t)next_time->tv_sec * 1000000U)
                             + (uint64_t)next_time->tv_usec;
    const uint64_t current_us = ((uint64_t)current_time.tv_sec * 1000000U)
                                + (uint64_t)current_time.tv_usec;

    if (next_us > current_us) {

        sleep_time = (rtems_interval)(((next_us - current_us)
                                       + TERMINA__TIME__MICROSECONDS_PER_TICK - 1U)
                                      / TERMINA__TIME__MICROSECONDS_PER_TICK);

    }

    return sleep_time;

}

static void termina__rtems__timer__task_connection_handler(
    rtems_id rtems_timer_id, void * input) {

    termina__shared__periodic_timer_t * timer = (termina__shared__periodic_timer_t *)input;
    termina__rtems__periodic_timer_t * rtems_timer = termina__rtems__timer__get_timer(timer->timer_id);

    termina__event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = timer->connection.task.task_id,
        .port_id = timer->connection.task.sink_port_id
    };

    termina__shared__msg_queue__deliver(timer->connection.task.sink_msgq_id,
                                        &rtems_timer->next_time,
                                        timer->connection.task.task_msg_queue_id,
                                        &event);

    termina__shared__add_timeval(&rtems_timer->next_time, &timer->period);

    // Arm the timer
    rtems_status_code arm_status = rtems_timer_fire_after(rtems_timer_id,
        get_sleep_time(&rtems_timer->next_time),
        termina__rtems__timer__task_connection_handler, input);

    if (RTEMS_SUCCESSFUL != arm_status) {

        termina__except__runtime_failure(termina__runtime_operation__timer_arm,
                                         termina__error__timer_arm);

    }

}

static void termina__rtems__timer__handler_connection_handler(
    rtems_id rtems_timer_id, void * input) {

    termina__shared__periodic_timer_t * timer = (termina__shared__periodic_timer_t *)input;
    termina__rtems__periodic_timer_t * rtems_timer = termina__rtems__timer__get_timer(timer->timer_id);

    Status__i32 ret;
    ret._variant = Status__Success;

    termina__event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = timer->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    ret = timer->connection.handler.handler_action(&event,
                                                   timer->connection.handler.handler_object,
                                                   rtems_timer->next_time);

    if (Status__Success != ret._variant) {

        termina__shared__except__handler_failure(timer->connection.handler.handler_id,
                                                 ret.Failure._0);

    } else {

        termina__shared__add_timeval(&rtems_timer->next_time, &timer->period);

        // Arm the timer
        rtems_status_code arm_status = rtems_timer_fire_after(rtems_timer_id,
            get_sleep_time(&rtems_timer->next_time),
            termina__rtems__timer__handler_connection_handler, input);

        if (RTEMS_SUCCESSFUL != arm_status) {

            termina__except__runtime_failure(termina__runtime_operation__timer_arm,
                                             termina__error__timer_arm);

        }

    }

}

void termina__periodic_timer_os__init(const termina__id_t timer_id,
                                       termina__error_code_t * const status) {

    termina__shared__periodic_timer_t * timer = termina__shared__timer__get_timer(timer_id);
    termina__rtems__periodic_timer_t * rtems_timer = termina__rtems__timer__get_timer(timer_id);

    *status = termina__error__none;

    // Install handler depending on the connection type
    if (termina__emitter_connection_type__handler == timer->connection.type) {

        rtems_timer->handler = termina__rtems__timer__handler_connection_handler;

    } else {

        rtems_timer->handler = termina__rtems__timer__task_connection_handler;

    }

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(ntimer_name[0], ntimer_name[1], ntimer_name[2],
            ntimer_name[3]);
    name = rtems_build_name(ntimer_name[0], ntimer_name[1], ntimer_name[2],
                            ntimer_name[3]);
    
    if (rtems_timer_create(name, &rtems_timer->rtems_timer_id) != RTEMS_SUCCESSFUL) {

	*status = termina__error__os_failure;

    }

    if (termina__error__none == *status) {

        termina__shared__add_timeval(&rtems_timer->next_time, &timer->period);

        // Arm the timer
        if (rtems_timer_fire_after(rtems_timer->rtems_timer_id,
                                   get_sleep_time(&rtems_timer->next_time),
                                   rtems_timer->handler, (void *)timer) != RTEMS_SUCCESSFUL) {

            *status = termina__error__timer_arm;

        }

    }

    return;

}
