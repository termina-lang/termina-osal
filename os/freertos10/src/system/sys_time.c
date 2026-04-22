
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>
#include <termina/os/freertos10/time.h>

#include <FreeRTOS.h>
#include "task.h"

void SystemEntry__clock_get_uptime(const __termina_event_t * const __ev,
                                   TimeVal * const uptime) {

    TickType_t current_ticks;

    if (__ev->owner.type == __termina_active_entity__handler) {
        current_ticks = xTaskGetTickCountFromISR();
    } else {
        /* task and timer: the timer daemon callback runs in task context */
        current_ticks = xTaskGetTickCount();
    }

    *uptime = __freertos_ticks_to_timeval(current_ticks);

    return;

}

void SystemEntry__delay_in(const __termina_event_t * const __ev,
                           const TimeVal * const time_val) {
    
    (void)__ev; // Unused parameter

    TickType_t delay_ticks = __freertos_timeval_to_ticks(*time_val);
    vTaskDelay(delay_ticks);

    return;

}

