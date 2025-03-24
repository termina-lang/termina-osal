
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>

#include <rtems.h>

/**
 * \brief This function returns the number of ticks per second.
 */
static inline uint64_t __rtems_time__ticks_per_sec(void) {
    return 1000000U / __TERMINA_MICROSECONDS_PER_TICK;
}

void __termina_sys_time__clock_get_uptime(TimeVal * const uptime) {

    struct timeval uptime_timeval;

    rtems_clock_get_uptime_timeval(&uptime_timeval);

    uptime->tv_sec = (uint32_t)uptime_timeval.tv_sec;
    uptime->tv_usec = (uint32_t)uptime_timeval.tv_usec;

}

void __termina_sys_time__delay_in(const TimeVal * const time_val) {

    rtems_interval sleep_time =
        (rtems_interval)(time_val->tv_sec * __rtems_time__ticks_per_sec()) +
        (rtems_interval)(time_val->tv_usec / __TERMINA_MICROSECONDS_PER_TICK);

    rtems_task_wake_after(sleep_time);

    return;

}

void __termina_sys_time__init_mutex(__termina_id_t mutex_id) {

    return;

}

void __termina_sys_time__init_task_lock() {

    return;

}

void __termina_sys_time__init_event_lock() {

    return;

}