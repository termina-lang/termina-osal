/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Common types of the OSAL: identifiers, error codes, events, active
 *        entities, locks, pools, boxes and output ports.
 */

#ifndef TERMINA__TYPES_H__
#define TERMINA__TYPES_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdatomic.h>

/**
 * @brief Type of the Termina object identifiers.
 */
typedef size_t termina__id_t;

/** @brief Identifier that denotes no object. */
#define TERMINA__ID__INVALID SIZE_MAX

/**
 * @brief Values of the status that the functions of the runtime return.
 *
 * The initialization of the application returns the function whose
 * initialization failed. An operation that fails while the application runs
 * returns the cause of the failure, which the exception that the failure
 * raises carries. Every back-end maps the errors of its operating system to
 * these causes, and to termina__error__os_failure the ones that have none.
 */
typedef enum {
    termina__error__none = 0,

    termina__error__msg_queue_init = 100,  /**< Creating a message queue. */
    termina__error__pool_init = 101,       /**< Initializing a pool. */
    termina__error__mutex_init = 102,      /**< Creating a mutex. */
    termina__error__timer_init = 103,      /**< Creating or arming a periodic timer. */
    termina__error__interrupt_init = 104,  /**< Installing an interrupt. */
    termina__error__task_init = 105,       /**< Creating a task. */

    termina__error__invalid_id = 200,      /**< Identifier out of range. */
    termina__error__queue_full = 201,      /**< The queue is full. */
    termina__error__receive_failed = 202,  /**< Receiving from the queue failed. */
    termina__error__no_memory = 203,       /**< No memory for the message. */
    termina__error__null_message = 204,    /**< The message is a null pointer. */
    termina__error__mutex_taken = 205,     /**< Another task holds the mutex. */
    termina__error__not_owner = 206,       /**< The caller does not hold the mutex. */
    termina__error__ceiling_violated = 207, /**< The caller is above the ceiling of the mutex. */
    termina__error__timer_arm = 208,       /**< The timer cannot be armed. */
    termina__error__task_ready = 209,      /**< The task cannot be made ready to run. */
    termina__error__invalid_block = 210,   /**< The address is not the start of a block of the pool. */
    termina__error__no_handler = 211,      /**< No handler is registered for the interrupt. */
    termina__error__deque_full = 212,      /**< The deque is full. */
    termina__error__invalid_priority = 213, /**< The priority is not the one of an application task. */

    termina__error__os_failure = 999       /**< Any other error of the operating system. */
} termina__error_code_t;

/**
 * @brief Kinds of active entity.
 */
typedef enum {
    termina__active_entity__task,
    termina__active_entity__handler
} termina__enum__active_entity_t;

/**
 * @brief Parameters of an active entity that is a task.
 */
typedef struct {
    //! Identifier of the task.
    termina__id_t task_id;
} termina__enum__active_entity__task_params_t;

/**
 * @brief Parameters of an active entity that is a handler.
 */
typedef struct {
    //! Identifier of the handler.
    termina__id_t handler_id;
} termina__enum__active_entity__handler_params_t;

/**
 * @brief Active entity, a task or a handler, on whose behalf an operation
 *        runs.
 */
typedef struct {
    termina__enum__active_entity_t type;
    union {
        termina__enum__active_entity__task_params_t task;
        termina__enum__active_entity__handler_params_t handler;
    };
} termina__active_entity_t;

/**
 * @brief Event that an active entity is processing.
 */
typedef struct {

    //! Identifier of the emitter.
    termina__id_t emitter_id;
    //! Active entity that processes the event.
    termina__active_entity_t owner;
    //! Identifier of the port of the entity.
    termina__id_t port_id;

} termina__event_t;

/**
 * @brief Kinds of lock that protect a resource.
 */
typedef enum {
    termina__resource_lock_type__none,
    termina__resource_lock_type__mutex,
    termina__resource_lock_type__irq
} termina__enum__resource_lock_type_t;

/**
 * @brief Parameters of a lock by mutex.
 */
typedef struct {
    //! Identifier of the mutex.
    termina__id_t mutex_id;
} termina__enum__resource_lock_type__mutex_params_t;

/**
 * @brief Parameters of a lock by interrupt masking.
 */
typedef struct {
    //! Identifier of the interrupt lock.
    termina__id_t lock_id;
} termina__enum__resource_lock_type__irq_params_t;

/**
 * @brief Lock that protects a resource.
 */
typedef struct {

    termina__enum__resource_lock_type_t type;

    termina__enum__resource_lock_type__mutex_params_t mutex;

    termina__enum__resource_lock_type__irq_params_t irq;

} termina__resource_lock_type_t;

/**
 * @brief Type of the pool global objects.
 */
typedef struct {

    termina__id_t pool_id;

    termina__resource_lock_type_t _lock_type;

} termina__pool_t;

/**
 * @brief Box: a block of a pool together with the pool it belongs to.
 */
typedef struct {

    //! Pointer to the data.
    void * data;

    //! Pointer to the pool that the data belongs to.
    termina__pool_t * pool;

} termina__box_t;

/**
 * @brief Enumeration of the possible variants of the Option type.
 */
typedef enum {
    Option__Some,
    Option__None
} termina__enum__Option_t;

/**
 * @brief Parameters of the `Some` variant of an option of a box.
 */
typedef struct {
    termina__box_t _0;
} termina__enum__Option__box__Some_params_t;

/**
 * @brief Structure that implements the Option type of a box.
 */
typedef struct {

    //! Current variant.
    termina__enum__Option_t _variant;

    //! Parameter of the `Some` variant.
    termina__enum__Option__box__Some_params_t Some;

} Option__box;

/**
 * @brief Type of the allocator interface.
 */
typedef struct {

    void * _that;
    void (*alloc) (const termina__event_t * const, void * const, Option__box * const);
    void (*free) (const termina__event_t * const, void * const, termina__box_t);

} termina__allocator_t;

/**
 * @brief Connection of an output port to the channel of a task.
 */
typedef struct {

    //! Identifier of the target task.
    termina__id_t task_id;

    //! Identifier of the port of the target task connected to the channel.
    termina__id_t port_id;

    //! Identifier of the event message queue of the target task.
    termina__id_t task_msg_queue_id;

    //! Identifier of the message queue of the channel.
    termina__id_t channel_msg_queue_id;

} termina__msg_queue_t;

/**
 * @brief Output port.
 */
typedef termina__msg_queue_t * termina__out_port_t;

/**
 * @brief Type of the system entry object.
 */
typedef struct {
    termina__resource_lock_type_t _lock_type;
} termina__system_entry_t;

#endif // TERMINA__TYPES_H__
