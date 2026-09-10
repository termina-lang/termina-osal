
#include <termina.h>

#include <termina/shared/mutex.h>

__termina_shared_mutex_t __shared_app_mutex_object_table[__TERMINA_SHARED_MUTEX_TABLE_SIZE];

void __termina_mutex__init(const __termina_id_t mutex_id,
                           const MutexProtocol protocol,
                           int32_t * const status) {

    *status = 0;

    if (!__termina_shared_mutex__is_valid_id(mutex_id)) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_shared_mutex_t * mutex = __termina_shared_mutex__get_mutex(mutex_id);

        mutex->mutex_id = mutex_id;
        mutex->protocol = protocol;

        __termina_os_mutex__init(mutex_id, status);

    }

}

void __termina_mutex__lock(const __termina_id_t mutex_id,
                           int32_t * const status) {

    *status = 0;

    if (!__termina_shared_mutex__is_valid_id(mutex_id)) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_os_mutex__lock(mutex_id, status);
    
    }

}

void __termina_mutex__unlock(const __termina_id_t mutex_id,
                             int32_t * const status) {

    *status = 0;

    if (!__termina_shared_mutex__is_valid_id(mutex_id)) {

        *status = -1;

    }    

    if (0 == *status) {

        __termina_os_mutex__unlock(mutex_id, status);
    
    }

}
