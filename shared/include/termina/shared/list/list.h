#ifndef __TERMINA__SHARED__LIST_H__
#define __TERMINA__SHARED__LIST_H__

/**
 * This file contains the declaration of the types and functions that
 * may be used to implement lists of identifiers.
 */

#include <termina.h>

struct __termina_shared_list_item {

    __termina_id_t obj_id;

    union {
        __termina_task_prio_t priority;
        TimeVal abs_time;
    };

    struct __termina_shared_list_item * next;

};

typedef struct __termina_shared_list_item __termina_shared_list_item_t;

typedef enum {

    __TERMINA_SHARED_LIST__FIFO,
    __TERMINA_SHARED_LIST__PRIORITY,
    __TERMINA_SHARED_LIST__TIME

} __termina_shared_list_type_t;

typedef struct {

    //! Pointer to the first element in the list
    __termina_shared_list_item_t * first;

    //! Pointer to the last element in the list
    __termina_shared_list_item_t * last;

    //! The number of items currently in the list
    size_t items;

    //! The type of the list
    __termina_shared_list_type_t list_type;

} __termina_shared_list_t;

/**
 * \brief Initializes a list.
 * 
 * This function initializes a list. It must be called before any other
 * operation is performed on the list.
 * 
 * @param[in]   list        the list to initialize.
 * @param[in]   list_type   the type of the list.
 * @param[out]  status      Success if OK, error otherwise. 
 */
void __termina_shared_list__init(__termina_shared_list_t * const list,
                                 __termina_shared_list_type_t list_type,
                                 Status * const status);

/**
 * \brief Adds an object to the list ordered by priority.
 * 
 * @param[inout] list      the list to which the object will be added.
 * @param[in]    obj_id    the identifier of the object to add.
 * @param[in]    priority  the priority of the object.
 * @param[out]   status    Success if OK, error otherwise.
 */
void __termina_shared_list__prio_add(__termina_shared_list_t * const list, 
                                     const __termina_id_t obj_id,
                                     const __termina_task_prio_t priority,
                                     Status * const status);

/**
 * \brief Adds an object to the list ordered by time.
 * 
 * @param[inout] list      the list to which the task will be added.
 * @param[in]    obj_id    the identifier of the task to add.
 * @param[in]    abs_time  the absolute time reference.
 * @param[out]   status    Success if OK, error otherwise.
 */
void __termina_shared_list__time_add(__termina_shared_list_t * const list, 
                                     const __termina_id_t obj_id,
                                     const TimeVal * const abs_time,
                                     Status * const status);

/**
 * \brief Appends an object to the end of the queue.
 * 
 * @param[inout] list    the list to which the object will be appended.
 * @param[in]    obj_id  the identifier of the object to append.
 * @param[out]   status  Success if OK, error otherwise.
 */
void __termina_shared_list__append(__termina_shared_list_t * const list,
                                   const __termina_id_t obj_id,
                                   Status * const status);

/**
 * \brief Extracts the first object from the list.
 * 
 * @param[inout] list    the list from which the object will be extracted.
 * 
 * @return the identifier of the extracted object. If the list is empty, the
 *         function returns TERMINA_INVALID_ID.
 */
__termina_id_t __termina_shared_list__extract(__termina_shared_list_t * const list);

/**
 * \brief Extracts the first object from the list that has a time less than the
 *        current time.
 * 
 * @param[inout] list         the list from which the object will be extracted.
 * @param[in]    current_time the current time.
 */
__termina_id_t __termina_shared_list__extract_time(__termina_shared_list_t * const list, 
                                                   const TimeVal * const current_time);

#endif // __TERMINA__SHARED__LIST_H__