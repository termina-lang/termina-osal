
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/system/sys_time.h>

void SystemEntry__clock_get_uptime(const __termina_event_t * const termina__ev,
                                   TimeVal * const uptime) {

    (void)termina__ev; // Unused parameter

    __termina_os_sys_time__clock_get_uptime(uptime);

    return;

}

void SystemEntry__delay_in(const __termina_event_t * const termina__ev,
                           const TimeVal * const time_val) {

    (void)termina__ev; // Unused parameter

    __termina_os_sys_time__delay_in(time_val);

    return;

}

