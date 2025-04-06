
#include <termina.h>
#include <termina/shared/list/list.h>

#include <stdlib.h>

void __termina_shared_list__init(__termina_shared_list_t * const list,
                                 __termina_shared_list_type_t list_type,
                                 Status * const status) {

    list->first = NULL;
    list->last = NULL;
    list->items = 0;
    list->list_type = list_type;

    status->__variant = Status__Success;

}

void __termina_shared_list__prio_add(__termina_shared_list_t * const list, 
                                     const __termina_id_t obj_id,
                                     const __termina_task_prio_t priority,
                                     Status * const status) {
    
    status->__variant = Status__Success;

    if (__TERMINA_SHARED_LIST__PRIORITY != list->list_type) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    if (priority > __TERMINA_TASK_MINIMUM_PRIORITY) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    __termina_shared_list_item_t * new_item = NULL;

    if (Status__Success == status->__variant) {

        // Allocate memory for the new item
        new_item = (__termina_shared_list_item_t *)malloc(sizeof(__termina_shared_list_item_t));

        if (NULL == new_item) {
            status->__variant = Status__Error;
            status->Error.__0.__variant = Exception__InternalError;
        }

    }

    if (Status__Success == status->__variant) {

        new_item->obj_id = obj_id;
        new_item->priority = priority;

        // Insert the item into the list in the correct position
        if (0 == list->items) {

            list->first = new_item;
            list->last = new_item;
            new_item->next = NULL;
            list->items = 1;

        } else {

            __termina_shared_list_item_t * current = list->first;
            __termina_shared_list_item_t * previous = NULL;

            while ((current != NULL) && (current->priority < priority)) {
                previous = current;
                current = current->next;
            }

            if (previous == NULL) {
                new_item->next = list->first;
                list->first = new_item;
            } else {
                new_item->next = current;
                previous->next = new_item;
            }

            if (current == NULL) {
                list->last = new_item;
            }

            list->items = list->items + 1;

        }

    }

}

void __termina_shared_list__time_add(__termina_shared_list_t * const list, 
                                   const __termina_id_t obj_id,
                                   const TimeVal * const abs_time,
                                   Status * const status) {

    status->__variant = Status__Success;

    if (list->list_type != __TERMINA_SHARED_LIST__TIME) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    __termina_shared_list_item_t * new_item = NULL;

    if (Status__Success == status->__variant) {

        // Allocate memory for the new item
        new_item = (__termina_shared_list_item_t *)malloc(sizeof(__termina_shared_list_item_t));

        if (NULL == new_item) {
            status->__variant = Status__Error;
            status->Error.__0.__variant = Exception__InternalError;
        }

    }

    if (Status__Success == status->__variant) {

        new_item->obj_id = obj_id;
        new_item->abs_time = *abs_time;

        // Insert the item into the list in the correct position
        if (0 == list->items) {

            list->first = new_item;
            list->last = new_item;
            new_item->next = NULL;
            list->items = 1;

        } else {

            __termina_shared_list_item_t * current = list->first;
            __termina_shared_list_item_t * previous = NULL;

            while (NULL != current) {

                uint64_t current_time = current->abs_time.tv_sec * 1000000 + current->abs_time.tv_usec;
                uint64_t new_time = abs_time->tv_sec * 1000000 + abs_time->tv_usec;

                if (new_time < current_time) {
                    break;
                }

                previous = current;
                current = current->next;
                
            }

            if (previous == NULL) {
                new_item->next = list->first;
                list->first = new_item;
            } else {
                new_item->next = current;
                previous->next = new_item;
            }

            if (current == NULL) {
                list->last = new_item;
            }

            list->items = list->items + 1;

        }

    }

}

void __termina_shared_list__append(__termina_shared_list_t * const list,
                                   const __termina_id_t obj_id,
                                   Status * const status) {

    status->__variant = Status__Success;

    if (list->list_type != __TERMINA_SHARED_LIST__FIFO) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    __termina_shared_list_item_t * new_item = NULL;

    if (Status__Success == status->__variant) {

        new_item = (__termina_shared_list_item_t *)malloc(sizeof(__termina_shared_list_item_t));

        if (NULL == new_item) {
            status->__variant = Status__Error;
            status->Error.__0.__variant = Exception__InternalError;
        }

    }

    if (Status__Success == status->__variant) {

        new_item->obj_id = obj_id;

        if (0 == list->items) {

            list->first = new_item;
            list->last = new_item;
            new_item->next = NULL;

        } else {

            list->last->next = new_item;
            list->last = new_item;
            new_item->next = NULL;

        }

        list->items = list->items + 1;

    }

}

__termina_id_t __termina_shared_list__extract(__termina_shared_list_t * const list) {

    __termina_id_t obj_id = __TERMINA_ID_INVALID;

    if (list->items > 0) {

        __termina_shared_list_item_t * item = list->first;

        obj_id = item->obj_id;

        list->first = item->next;

        free(item);

        if (1 == list->items) {
            list->last = NULL;
        }

        list->items = list->items - 1;

    }

    return obj_id;

}

__termina_id_t __termina_shared_list__extract_time(__termina_shared_list_t * const list, 
                                                   const TimeVal * const current_time) {

    __termina_id_t obj_id = __TERMINA_ID_INVALID;

    if (list->items > 0) {

        __termina_shared_list_item_t * item = list->first;

        uint64_t item_time = item->abs_time.tv_sec * 1000000 + item->abs_time.tv_usec;
        uint64_t current_time_val = current_time->tv_sec * 1000000 + current_time->tv_usec;

        if (item_time <= current_time_val) {

            obj_id = item->obj_id;

            list->first = item->next;

            free(item);

            if (1 == list->items) {
                list->last = NULL;
            }

            list->items = list->items - 1;

        }

    }

    return obj_id;

}
