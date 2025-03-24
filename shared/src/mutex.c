
#include <termina.h>

#include <termina/shared/mutex.h>

__termina_shared_mutex_t __shared_app_mutex_object_table[__TERMINA_APP_CONFIG_MUTEXES];

void __termina_mutex__init(const __termina_id_t mutex_id,
                           __termina_mutex_policy_t policy,
                           __termina_task_prio_t prio_ceiling,
                           Status * const status) {

    status->__variant = Status__Success;

    if (mutex_id >= __TERMINA_APP_CONFIG_MUTEXES) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    if (Status__Success == status->__variant) {

        __termina_shared_mutex_t * mutex = __termina_shared_mutex__get_mutex(mutex_id);

        mutex->mutex_id = mutex_id;
        mutex->policy = policy;
        mutex->prio_ceiling = prio_ceiling;

        __termina_os_mutex__init(mutex_id, status);

    }

}

void __termina_mutex__lock(const __termina_id_t mutex_id,
                           Status * const status) {

    status->__variant = Status__Success;

    if (mutex_id >= __TERMINA_APP_CONFIG_MUTEXES) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    if (Status__Success == status->__variant) {

        __termina_os_mutex__lock(mutex_id, status);
    
    }

}

void __termina_mutex__unlock(const __termina_id_t mutex_id,
                             Status * const status) {

    status->__variant = Status__Success;

    if (mutex_id >= __TERMINA_APP_CONFIG_MUTEXES) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }    

    if (Status__Success == status->__variant) {

        __termina_os_mutex__unlock(mutex_id, status);
    
    }

}