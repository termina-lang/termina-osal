
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>
#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>

void SystemEntry__clock_get_uptime(TimeVal * const uptime) {

    __posix_time__get_current_time(uptime);

}

void SystemEntry__delay_in(const TimeVal * const time_val) {

    Status status;
    status.__variant = Status__Success;

    TimeVal current_time = {0, 0};
    __posix_time__get_current_time(&current_time);

    __termina_shared__add_timeval(&current_time, time_val);

    __termina_shared_list__time_add(&__posix_delayed_tasks_list, 
                                    __posix_current_task_id, &current_time, &status);

    if (Status__Success == status.__variant) {

        if (0 == __posix_task__disable_scheduling) {
            __posix_task__yield();
        }
    
    }

    return;

}

