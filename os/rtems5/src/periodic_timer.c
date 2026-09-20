
#include <termina.h>

#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/rtems5/name.h>

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

static rtems_interval get_sleep_time(const TimeVal * const next_time) {

    rtems_interval sleep_time = 0;

    struct timeval current_time;
    current_time.tv_sec = 0;
    current_time.tv_usec = 0;

    rtems_clock_get_uptime_timeval(&current_time);

    if (next_time->tv_sec > current_time.tv_sec) {

        TimeVal interval;
        interval.tv_sec = 0;
        interval.tv_usec = 0;

        if (next_time->tv_usec >= (uint32_t)current_time.tv_usec) {

            interval.tv_sec = (uint32_t)(next_time->tv_sec - current_time.tv_sec);
            interval.tv_usec = next_time->tv_usec - (uint32_t)current_time.tv_usec;

        } else {

            interval.tv_sec = (uint32_t)(next_time->tv_sec - current_time.tv_sec) - 1;
            interval.tv_usec = 1000000 -
                ((uint32_t)current_time.tv_usec - next_time->tv_usec);

        }

        // Calculate the sleep time
        sleep_time = (rtems_interval)(interval.tv_sec * termina___get_ticks_per_sec()) +
                     (rtems_interval)(interval.tv_usec / TERMINA__TIME__MICROSECONDS_PER_TICK);

        // If the microseconds are not a multiple of the tick, we need to add one tick
        if ((interval.tv_usec % TERMINA__TIME__MICROSECONDS_PER_TICK) != 0) {

            sleep_time = sleep_time + 1;

        }


    } else if (next_time->tv_sec == current_time.tv_sec) {

        if (next_time->tv_usec > (uint32_t)current_time.tv_usec) {

            TimeVal interval;

            interval.tv_sec = 0;
            interval.tv_usec = next_time->tv_usec - (uint32_t)current_time.tv_usec;

            sleep_time = (rtems_interval)(interval.tv_usec / TERMINA__TIME__MICROSECONDS_PER_TICK);

        }

    } else {

        // Do nothing

    }


    return sleep_time;

}

static void termina__rtems__timer__task_connection_handler(
    rtems_id rtems_timer_id, void * input) {

    termina__shared__periodic_timer_t * timer = (termina__shared__periodic_timer_t *)input;
    termina__rtems__periodic_timer_t * rtems_timer = termina__rtems__timer__get_timer(timer->timer_id);

    int32_t status = 0;

    termina__event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = timer->connection.task.task_id,
        .port_id = timer->connection.task.sink_port_id
    };

    // Send a message to the task
    termina__msg_queue__send(timer->connection.task.sink_msgq_id,
                              &rtems_timer->next_time, &status);
    termina__msg_queue__send(timer->connection.task.task_msg_queue_id,
                              &event, &status);
    // TODO: Check return status

    termina__shared__add_timeval(&rtems_timer->next_time, &timer->period);

    // Arm the timer
    rtems_timer_fire_after(rtems_timer_id, get_sleep_time(&rtems_timer->next_time),
                           termina__rtems__timer__task_connection_handler, input);
    

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

        termina__exec__reboot();

    } else {

        termina__shared__add_timeval(&rtems_timer->next_time, &timer->period);

        // Arm the timer
        rtems_timer_fire_after(rtems_timer_id, get_sleep_time(&rtems_timer->next_time),
                               termina__rtems__timer__handler_connection_handler, input);
    }

}

void termina__periodic_timer_os__init(const termina__id_t timer_id,
                                       int32_t *const status) {

    termina__shared__periodic_timer_t * timer = termina__shared__timer__get_timer(timer_id);
    termina__rtems__periodic_timer_t * rtems_timer = termina__rtems__timer__get_timer(timer_id);

    *status = 0;

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

	*status = -1;

    }

    if (0 == *status) {

        termina__shared__add_timeval(&rtems_timer->next_time, &timer->period);

        // Arm the timer
        rtems_timer_fire_after(rtems_timer->rtems_timer_id, 
                               get_sleep_time(&rtems_timer->next_time),
                               rtems_timer->handler, (void *)timer);

    }

    return;

}
