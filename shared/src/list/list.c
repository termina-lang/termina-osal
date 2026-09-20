
#include <termina.h>
#include <termina/shared/list/list.h>

#include <stdlib.h>

void termina__shared_list__init(termina__shared_list_t * const list,
                                 termina__shared_list_type_t list_type,
                                 int32_t * const status) {

    list->first = NULL;
    list->last = NULL;
    list->items = 0;
    list->list_type = list_type;

    *status = 0;

}

void termina__shared_list__prio_add(termina__shared_list_t * const list, 
                                     const termina__id_t obj_id,
                                     const termina__task_prio_t priority,
                                     int32_t * const status) {
    
    *status = 0;

    if (TERMINA__SHARED_LIST__PRIORITY != list->list_type) {

        *status = -1;

    }

    termina__shared_list_item_t * new_item = NULL;

    if (0 == *status) {

        // Allocate memory for the new item
        new_item = (termina__shared_list_item_t *)malloc(sizeof(termina__shared_list_item_t));

        if (NULL == new_item) {

            *status = -1;

        }

    }

    if (0 == *status) {

        new_item->obj_id = obj_id;
        new_item->priority = priority;

        // Insert the item into the list in the correct position
        if (0 == list->items) {

            list->first = new_item;
            list->last = new_item;
            new_item->next = NULL;
            list->items = 1;

        } else {

            termina__shared_list_item_t * current = list->first;
            termina__shared_list_item_t * previous = NULL;

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

void termina__shared_list__time_add(termina__shared_list_t * const list, 
                                   const termina__id_t obj_id,
                                   const TimeVal * const abs_time,
                                   int32_t * const status) {

    *status = 0;

    if (list->list_type != TERMINA__SHARED_LIST__TIME) {

        *status = -1;

    }

    termina__shared_list_item_t * new_item = NULL;

    if (0 == *status) {

        // Allocate memory for the new item
        new_item = (termina__shared_list_item_t *)malloc(sizeof(termina__shared_list_item_t));

        if (NULL == new_item) {

            *status = -1;

        }

    }

    if (0 == *status) {

        new_item->obj_id = obj_id;
        new_item->abs_time = *abs_time;

        // Insert the item into the list in the correct position
        if (0 == list->items) {

            list->first = new_item;
            list->last = new_item;
            new_item->next = NULL;
            list->items = 1;

        } else {

            termina__shared_list_item_t * current = list->first;
            termina__shared_list_item_t * previous = NULL;

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

void termina__shared_list__append(termina__shared_list_t * const list,
                                   const termina__id_t obj_id,
                                   int32_t * const status) {

    *status = 0;

    if (list->list_type != TERMINA__SHARED_LIST__FIFO) {

        *status = -1;

    }

    termina__shared_list_item_t * new_item = NULL;

    if (0 == *status) {

        new_item = (termina__shared_list_item_t *)malloc(sizeof(termina__shared_list_item_t));

        if (NULL == new_item) {

            *status = -1;

        }

    }

    if (0 == *status) {

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

termina__id_t termina__shared_list__extract(termina__shared_list_t * const list) {

    termina__id_t obj_id = TERMINA__ID__INVALID;

    if (list->items > 0) {

        termina__shared_list_item_t * item = list->first;

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

termina__id_t termina__shared_list__extract_time(termina__shared_list_t * const list, 
                                                   const TimeVal * const current_time) {

    termina__id_t obj_id = TERMINA__ID__INVALID;

    if (list->items > 0) {

        termina__shared_list_item_t * item = list->first;

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
