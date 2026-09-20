
#include <termina.h>

#include <termina/shared/mutex.h>

termina__shared__mutex_t termina__shared__app_mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

void termina__mutex__init(const termina__id_t mutex_id,
                           const MutexProtocol protocol,
                           int32_t * const status) {

    *status = 0;

    if (!termina__shared__mutex__is_valid_id(mutex_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__shared__mutex_t * mutex = termina__shared__mutex__get_mutex(mutex_id);

        mutex->mutex_id = mutex_id;
        mutex->protocol = protocol;

        termina__os__mutex__init(mutex_id, status);

    }

}

void termina__mutex__lock(const termina__id_t mutex_id,
                           int32_t * const status) {

    *status = 0;

    if (!termina__shared__mutex__is_valid_id(mutex_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__os__mutex__lock(mutex_id, status);
    
    }

}

void termina__mutex__unlock(const termina__id_t mutex_id,
                             int32_t * const status) {

    *status = 0;

    if (!termina__shared__mutex__is_valid_id(mutex_id)) {

        *status = -1;

    }    

    if (0 == *status) {

        termina__os__mutex__unlock(mutex_id, status);
    
    }

}
