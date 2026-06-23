
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>
#include <termina/os/freertos10/time.h>

#include <FreeRTOS.h>
#include "task.h"

void __termina_os_sys_time__clock_get_uptime(TimeVal * const uptime) {

    TickType_t current_ticks;

    if (xPortIsInsideInterrupt()) {
        current_ticks = xTaskGetTickCountFromISR();
    } else {
        /* task and timer: the timer daemon callback runs in task context */
        current_ticks = xTaskGetTickCount();
    }

    *uptime = __freertos_ticks_to_timeval(current_ticks);

    return;

}

void __termina_os_sys_time__delay_in(const TimeVal * const time_val) {
    
    TickType_t delay_ticks = __freertos_timeval_to_ticks(*time_val);

    vTaskDelay(delay_ticks);

    return;

}

