
#include <termina.h>

#include <termina/shared/mutex.h>

termina__shared__mutex_t termina__shared__mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

void termina__mutex__init(const termina__id_t mutex_id,
                           const MutexProtocol protocol,
                           termina__error_code_t * const status) {

    *status = termina__error__none;

    if (!termina__shared__mutex__is_valid_id(mutex_id)) {

        *status = termina__error__invalid_id;

    }

    if (termina__error__none == *status) {

        termina__shared__mutex_t * mutex = termina__shared__mutex__get_mutex(mutex_id);

        mutex->mutex_id = mutex_id;
        mutex->protocol = protocol;

        termina__os__mutex__init(mutex_id, status);

    }

    if (termina__error__none != *status) {

        *status = termina__error__mutex_init;

    }

}

void termina__mutex__lock(const termina__id_t mutex_id,
                           termina__error_code_t * const status) {

    *status = termina__error__none;

    if (!termina__shared__mutex__is_valid_id(mutex_id)) {

        *status = termina__error__invalid_id;

    }

    if (termina__error__none == *status) {

        termina__os__mutex__lock(mutex_id, status);
    
    }

}

void termina__mutex__unlock(const termina__id_t mutex_id,
                             termina__error_code_t * const status) {

    *status = termina__error__none;

    if (!termina__shared__mutex__is_valid_id(mutex_id)) {

        *status = termina__error__invalid_id;

    }    

    if (termina__error__none == *status) {

        termina__os__mutex__unlock(mutex_id, status);
    
    }

}
