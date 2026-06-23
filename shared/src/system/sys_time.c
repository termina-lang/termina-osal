
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/system/sys_time.h>

void SystemEntry__clock_get_uptime(const __termina_event_t * const __ev,
                                   TimeVal * const uptime) {

    (void)__ev; // Unused parameter

    __termina_os_sys_time__clock_get_uptime(uptime);

    return;

}

void SystemEntry__delay_in(const __termina_event_t * const __ev,
                           const TimeVal * const time_val) {

    (void)__ev; // Unused parameter

    __termina_os_sys_time__delay_in(time_val);

    return;

}

