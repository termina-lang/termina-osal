
#include <termina.h>

#include <termina/shared/list.h>
#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_timer_id;

    rtems_timer_service_routine_entry handler;

    TimeVal next_time;

} __rtems_periodic_timer_t;

extern __rtems_periodic_timer_t __rtems_periodic_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

static inline __rtems_periodic_timer_t * __rtems_timer__get_timer(const __termina_id_t timer_id) {
    return &__rtems_periodic_timers[timer_id];
}


__rtems_periodic_timer_t __rtems_periodic_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

/**
 * \brief Array used to generate the names of the timers that are created.
 */
static int8_t ntimer_name[5]  = "0000";

static inline uint64_t get_ticks_per_sec(void) {
    return 1000000U / __TERMINA_MICROSECONDS_PER_TICK;
}

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

        if (next_time->tv_usec >= current_time.tv_usec) {

            interval.tv_sec = next_time->tv_sec - current_time.tv_sec;
            interval.tv_usec = next_time->tv_usec - current_time.tv_usec;

        } else {

            interval.tv_sec = (uint32_t)(next_time->tv_sec - current_time.tv_sec) - 1;
            interval.tv_usec = 1000000 -
                (uint32_t)(current_time.tv_usec - next_time->tv_usec);

        }

        // Calculate the sleep time
        sleep_time = (rtems_interval)(interval.tv_sec * get_ticks_per_sec()) +
                     (rtems_interval)(interval.tv_usec / __TERMINA_MICROSECONDS_PER_TICK);

        // If the microseconds are not a multiple of the tick, we need to add one tick
        if ((interval.tv_usec % __TERMINA_MICROSECONDS_PER_TICK) != 0) {

            sleep_time = sleep_time + 1;

        }


    } else if (next_time->tv_sec == current_time.tv_sec) {

        if (next_time->tv_usec > current_time.tv_usec) {

            TimeVal interval;

            interval.tv_sec = 0;
            interval.tv_usec = next_time->tv_usec - current_time.tv_usec;

            sleep_time = (rtems_interval)(interval.tv_usec / __TERMINA_MICROSECONDS_PER_TICK);

        }

    } else {

        // Do nothing

    }


    return sleep_time;

}

static void __rtems_timer__task_connection_handler(
    rtems_id rtems_timer_id, void * input) {

    __termina_shared_periodic_timer_t * timer = (__termina_shared_periodic_timer_t *)input;
    __rtems_periodic_timer_t * rtems_timer = __rtems_timer__get_timer(timer->timer_id);

    Status status;
    status.__variant = Status__Success;

    // Send a message to the task
    __termina_msg_queue__send(timer->connection.task.sink_msgq_id,
                              &rtems_timer->next_time, &status);
    __termina_msg_queue__send(timer->connection.task.task_msgq_id,
                              &timer->connection.task.sink_port_id, &status);
    // TODO: Check return status

    __termina_shared__add_timeval(&rtems_timer->next_time, &timer->period);

    // Arm the timer
    rtems_timer_fire_after(rtems_timer_id, get_sleep_time(&rtems_timer->next_time),
                           __rtems_timer__task_connection_handler, input);
    

}

static void __rtems_timer__handler_connection_handler(
    rtems_id rtems_timer_id, void * input) {

    __termina_shared_periodic_timer_t * timer = (__termina_shared_periodic_timer_t *)input;
    __rtems_periodic_timer_t * rtems_timer = __rtems_timer__get_timer(timer->timer_id);

    Result result;

    result = timer->connection.handler.handler_action(timer->connection.handler.handler_object,
                                                      rtems_timer->next_time);

    if (Result__Ok != result.__variant) {

        __termina_exec__shutdown();

    } else {

        __termina_shared__add_timeval(&rtems_timer->next_time, &timer->period);

        // Arm the timer
        rtems_timer_fire_after(rtems_timer_id, get_sleep_time(&rtems_timer->next_time),
                               __rtems_timer__task_connection_handler, input);
    }

}

void __termina_periodic_timer_os__init(const __termina_id_t timer_id,
                                       Status *const status) {

    __termina_shared_periodic_timer_t * timer = __termina_shared_timer__get_timer(timer_id);
    __rtems_periodic_timer_t * rtems_timer = __rtems_timer__get_timer(timer_id);

    status->__variant = Status__Success;

    // Install handler depending on the connection type
    if (timer->connection.type == __TerminaEmitterConnectionType__Handler) {

        rtems_timer->handler = __rtems_timer__handler_connection_handler;

    } else {

        rtems_timer->handler = __rtems_timer__task_connection_handler;

    }

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(ntimer_name[0], ntimer_name[1], ntimer_name[2],
            ntimer_name[3]);
    name = rtems_build_name(ntimer_name[0], ntimer_name[1], ntimer_name[2],
                            ntimer_name[3]);
    
    if (rtems_timer_create(name, &rtems_timer->rtems_timer_id) != RTEMS_SUCCESSFUL) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    if (Status__Success == status->__variant) {

        __termina_shared__add_timeval(&rtems_timer->next_time, &timer->period);

        // Arm the timer
        rtems_timer_fire_after(rtems_timer->rtems_timer_id, 
                               get_sleep_time(&rtems_timer->next_time),
                               __rtems_timer__task_connection_handler, (void *)timer);

    }

    return;

}
