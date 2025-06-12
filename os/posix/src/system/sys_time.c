
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>
#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>

void SystemEntry__clock_get_uptime(const __termina_event_t * const __ev,
                                   TimeVal * const uptime) {

    (void)__ev; // Unused parameter
    __posix_time__get_current_time(uptime);

}

void SystemEntry__delay_in(const __termina_event_t * const __ev,
                           const TimeVal * const time_val) {

    (void)__ev; // Unused parameter

    int32_t status = 0;

    TimeVal current_time = {0, 0};
    __posix_time__get_current_time(&current_time);

    __termina_shared__add_timeval(&current_time, time_val);

    __termina_shared_list__time_add(&__posix_delayed_tasks_list, 
                                    __posix_current_task_id, &current_time, &status);

    if (0 == status) {

        if (0 == __posix_task__disable_scheduling) {
            __posix_task__yield();
        }
    
    }

    return;

}

