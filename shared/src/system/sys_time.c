
#include <termina.h>

#include <termina/shared/system/sys_time.h>

__termina_sys_time_t __termina_sys_time;

void __termina_sys_time__clock_get_uptime_mutex(TimeVal * const uptime) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_time.mutex_id, &status);
    __termina_sys_time__clock_get_uptime(uptime);
    __termina_mutex__unlock(__termina_sys_time.mutex_id, &status);
    // TODO: Check status

    return;

}

void __termina_sys_time__delay_in_mutex(const TimeVal * const time_val) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_time.mutex_id, &status);
    __termina_sys_time__delay_in(time_val);
    __termina_mutex__unlock(__termina_sys_time.mutex_id, &status);
    // TODO: Check status

    return;

}

void __termina_sys_time__init() {

    __termina_sys_time.clock_get_uptime = __termina_sys_time__clock_get_uptime;
    __termina_sys_time.delay_in = __termina_sys_time__delay_in;

    return;

}