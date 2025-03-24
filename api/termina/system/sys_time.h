#ifndef __TERMINA__SYSTEM__SYS_TIME_H__
#define __TERMINA__SYSTEM__SYS_TIME_H__

#include <termina/types.h>
#include <termina/prelude.h>

typedef struct {

    // \brief Mutex used to protect the system time functions
    __termina_id_t mutex_id;

    // \brief Get the current uptime
    void (*clock_get_uptime)(TimeVal * const uptime);
    // \brief Block the calling task for a given amount of time
    void (*delay_in)(const TimeVal * const time_val);

} __termina_sys_time_t;

extern __termina_sys_time_t __termina_sys_time;

void __termina_sys_time__init();
void __termina_sys_time__init_mutex(__termina_id_t mutex_id);
void __termina_sys_time__init_task_lock();
void __termina_sys_time__init_event_lock();

#endif // __TERMINA__SYSTEM__SYS_TIME_H__