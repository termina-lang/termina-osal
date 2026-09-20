
#include <termina.h>

#include <termina/shared/time.h>
#include <termina/shared/system/sys_time.h>
#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>

void termina__os__sys_time__clock_get_uptime(TimeVal * const uptime) {

    termina__posix__time__get_current_time(uptime);

    return;

}

void termina__os__sys_time__delay_in(const TimeVal * const time_val) {

    int32_t status = 0;

    TimeVal current_time = {0, 0};
    termina__posix__time__get_current_time(&current_time);

    termina__shared__add_timeval(&current_time, time_val);

    termina__shared__list__time_add(&termina__posix__delayed_tasks_list, 
                                    termina__posix__current_task_id, &current_time, &status);

    if (0 == status) {

        if (0 == termina__posix__task__disable_scheduling) {
            termina__posix__task__yield();
        }
    
    }

    return;

}

