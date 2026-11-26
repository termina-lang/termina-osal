/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Lists of object identifiers ordered in FIFO order, by priority or by
 *        time.
 */

#ifndef TERMINA__SHARED__LIST_H__
#define TERMINA__SHARED__LIST_H__

#include <termina.h>

/**
 * @brief Item of a list.
 */
struct termina__shared__list_item {

    //! Identifier of the object.
    termina__id_t obj_id;

    union {
        //! Priority, in a list by priority.
        termina__task_prio_t priority;
        //! Absolute time, in a list by time.
        TimeVal abs_time;
    };

    //! Next item of the list.
    struct termina__shared__list_item * next;

};

/** @brief Type of the items of a list. */
typedef struct termina__shared__list_item termina__shared__list_item_t;

/**
 * @brief Order of a list.
 */
typedef enum {

    TERMINA__SHARED_LIST__FIFO,
    TERMINA__SHARED_LIST__PRIORITY,
    TERMINA__SHARED_LIST__TIME

} termina__shared__list_type_t;

/**
 * @brief List of object identifiers.
 */
typedef struct {

    //! Pointer to the first item of the list.
    termina__shared__list_item_t * first;

    //! Pointer to the last item of the list.
    termina__shared__list_item_t * last;

    //! Number of items in the list.
    size_t items;

    //! Order of the list.
    termina__shared__list_type_t list_type;

} termina__shared__list_t;

/**
 * @brief Initializes an empty list.
 * 
 * The function must be called before any other operation on the list.
 * 
 * @param[out]  list       Pointer to the list.
 * @param[in]   list_type  Order of the list.
 * @param[out]  status     Status of the operation: `termina__error__none`.
 */
void termina__shared__list__init(termina__shared__list_t * const list,
                                 termina__shared__list_type_t list_type,
                                 termina__error_code_t * const status);

/**
 * @brief Adds an object to a list ordered by priority.
 * 
 * @param[in,out] list      Pointer to the list.
 * @param[in]     obj_id    Identifier of the object to add.
 * @param[in]     priority  Priority of the object.
 * @param[out]    status    Status of the operation: `termina__error__none`,
 *                          or `termina__error__os_failure` if the list is not
 *                          ordered by priority or the item cannot be
 *                          allocated.
 */
void termina__shared__list__prio_add(termina__shared__list_t * const list, 
                                     const termina__id_t obj_id,
                                     const termina__task_prio_t priority,
                                     termina__error_code_t * const status);

/**
 * @brief Adds an object to a list ordered by time.
 * 
 * @param[in,out] list      Pointer to the list.
 * @param[in]     obj_id    Identifier of the object to add.
 * @param[in]     abs_time  Absolute time of the object.
 * @param[out]    status    Status of the operation: `termina__error__none`,
 *                          or `termina__error__os_failure` if the list is not
 *                          ordered by time or the item cannot be allocated.
 */
void termina__shared__list__time_add(termina__shared__list_t * const list, 
                                     const termina__id_t obj_id,
                                     const TimeVal * const abs_time,
                                     termina__error_code_t * const status);

/**
 * @brief Appends an object to the end of a list.
 * 
 * @param[in,out] list    Pointer to the list.
 * @param[in]     obj_id  Identifier of the object to append.
 * @param[out]    status  Status of the operation: `termina__error__none`, or
 *                        `termina__error__os_failure` if the list is not a
 *                        FIFO list or the item cannot be allocated.
 */
void termina__shared__list__append(termina__shared__list_t * const list,
                                   const termina__id_t obj_id,
                                   termina__error_code_t * const status);

/**
 * @brief Prepends an object to the start of a list.
 *
 * @param[in,out] list    Pointer to the list.
 * @param[in]     obj_id  Identifier of the object to prepend.
 * @param[out]    status  Status of the operation: `termina__error__none`, or
 *                        `termina__error__os_failure` if the list is not a
 *                        FIFO list or the item cannot be allocated.
 */
void termina__shared__list__prepend(termina__shared__list_t * const list,
                                    const termina__id_t obj_id,
                                    termina__error_code_t * const status);

/**
 * @brief Extracts the first object of a list.
 * 
 * @param[in,out] list  Pointer to the list.
 * 
 * @return The identifier of the extracted object, or `TERMINA__ID__INVALID`
 *         if the list is empty.
 */
termina__id_t termina__shared__list__extract(termina__shared__list_t * const list);

/**
 * @brief Extracts the first object of a list if its time is less than the
 *        current time.
 * 
 * @param[in,out] list          Pointer to the list.
 * @param[in]     current_time  Current time.
 *
 * @return The identifier of the extracted object, or `TERMINA__ID__INVALID`
 *         if no object is extracted.
 */
termina__id_t termina__shared__list__extract_time(termina__shared__list_t * const list, 
                                                   const TimeVal * const current_time);

#endif // TERMINA__SHARED__LIST_H__
