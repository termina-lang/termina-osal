#ifndef TERMINA__TYPES_H__
#define TERMINA__TYPES_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdatomic.h>

/**
 * \brief Type of the Termina object identifiers.
 */
typedef size_t termina__id_t;

#define TERMINA__ID__INVALID SIZE_MAX

typedef enum {
    termina__active_entity__task,
    termina__active_entity__handler
} termina__enum__active_entity_t;

typedef struct {
    termina__id_t task_id;
} termina__enum__active_entity__task_params_t;

typedef struct {
    termina__id_t handler_id;
} termina__enum__active_entity__handler_params_t;

typedef struct {
    termina__enum__active_entity_t type;
    union {
        termina__enum__active_entity__task_params_t task;
        termina__enum__active_entity__handler_params_t handler;
    };
} termina__active_entity_t;

typedef struct {

    termina__id_t emitter_id;
    termina__active_entity_t owner;
    termina__id_t port_id;

} termina__event_t;

typedef enum {
    termina__resource_lock_type__none,
    termina__resource_lock_type__mutex,
    termina__resource_lock_type__irq
} termina__enum__resource_lock_type_t;

typedef struct {
    termina__id_t mutex_id;
} termina__enum__resource_lock_type__mutex_params_t;

typedef struct {
    
    termina__enum__resource_lock_type_t type;

    termina__enum__resource_lock_type__mutex_params_t mutex;

} termina__resource_lock_type_t;

/**
 * \brief Type of the pool global objects.
 */
typedef struct {

    termina__id_t pool_id;

    termina__resource_lock_type_t _lock_type;

} termina__pool_t;

typedef struct {

    // \brief Pointer to the data 
    void * data;

    // \brief Pointer to the pool that originated the data
    termina__pool_t * pool;

} termina__box_t;

/**
 * \brief Enumeration of the possible variants of the Option type.
 */
typedef enum {
    Option__Some,
    Option__None
} termina__enum__Option_t;

typedef struct {
    termina__box_t _0;
} termina__enum__Option__box__Some_params_t;

/**
 * \brief Structure used to implement the dynamic subtyping relationship.
 */
typedef struct {

    // \brief The current variant.
    termina__enum__Option_t _variant;

    // \brief The parameter of the Somevariant.
    termina__enum__Option__box__Some_params_t Some;

} Option__box;

/**
 * \brief Type of the allocator interface.
 */
typedef struct {

    void * _that;
    void (*alloc) (const termina__event_t * const, void * const, Option__box * const);
    void (*free) (const termina__event_t * const, void * const, termina__box_t);

} termina__allocator_t;

typedef struct {

    // \brief Identifier of the target task.
    termina__id_t task_id;

    // \brief Identifier of the target task's port connected to the channel.
    termina__id_t port_id;

    // \brief Identifier of the target task's event message queue.
    termina__id_t task_msg_queue_id;

    // \brief Identifier of the channel message queue.
    termina__id_t channel_msg_queue_id;

} termina__msg_queue_t;

typedef termina__msg_queue_t * termina__out_port_t;

typedef struct {
    termina__resource_lock_type_t _lock_type;
} termina__system_entry_t;

#endif // TERMINA__TYPES_H__
