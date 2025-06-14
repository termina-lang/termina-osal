
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

void SystemEntry__clock_get_uptime(const __termina_event_t * const __ev,
                                   TimeVal * const uptime) {

    (void)__ev; // Unused parameter

    struct timeval uptime_timeval;

    rtems_clock_get_uptime_timeval(&uptime_timeval);

    uptime->tv_sec = (uint32_t)uptime_timeval.tv_sec;
    uptime->tv_usec = (uint32_t)uptime_timeval.tv_usec;

}

void SystemEntry__delay_in(const __termina_event_t * const __ev,
                           const TimeVal * const time_val) {
    
    (void)__ev; // Unused parameter

    rtems_interval sleep_time =
        (rtems_interval)(time_val->tv_sec * __rtems_time__ticks_per_sec()) +
        (rtems_interval)(time_val->tv_usec / __TERMINA_MICROSECONDS_PER_TICK);

    rtems_task_wake_after(sleep_time);

    return;

}

