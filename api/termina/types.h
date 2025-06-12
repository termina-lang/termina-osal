#ifndef __TERMINA__TYPES_H__
#define __TERMINA__TYPES_H__

#include <stdint.h>
#include <stddef.h>
#include <stdatomic.h>

/**
 * \brief Type of the Termina object identifiers.
 */
typedef size_t __termina_id_t;

#define __TERMINA_ID_INVALID SIZE_MAX

typedef enum {
    __termina_active_entity__task,
    __termina_active_entity__handler
} __enum_termina_active_entity_t;

typedef struct {
    __termina_id_t task_id;
} __enum_termina_active_entity__task_params_t;

typedef struct {
    __termina_id_t handler_id;
} __enum_termina_active_entity__handler_params_t;

typedef struct {
    __enum_termina_active_entity_t type;
    union {
        __enum_termina_active_entity__task_params_t task;
        __enum_termina_active_entity__handler_params_t handler;
    };
} __termina_active_entity_t;

typedef struct {

    __termina_id_t emitter_id;
    __termina_active_entity_t owner;
    __termina_id_t port_id;

} __termina_event_t;

typedef enum {
    __termina_resource_lock_type__none,
    __termina_resource_lock_type__mutex,
    __termina_resource_lock_type__irq
} __enum_termina_resource_lock_type_t;

typedef struct {
    __termina_id_t mutex_id;
} __enum_termina_resource_lock_type__mutex_params_t;

typedef struct {
    
    __enum_termina_resource_lock_type_t type;

    __enum_termina_resource_lock_type__mutex_params_t mutex;

} __termina_resource_lock_type_t;

/**
 * \brief Type of the pool global objects.
 */
typedef struct {

    __termina_id_t __pool_id;

    __termina_resource_lock_type_t __lock_type;

} __termina_pool_t;

typedef struct {

    // \brief Pointer to the data 
    void * data;

    // \brief Pointer to the pool that originated the data
    __termina_pool_t * pool;

} __termina_box_t;

/**
 * \brief Enumeration of the possible variants of the Option type.
 */
typedef enum {
    Some,
    None
} __enum_option_t;

typedef struct {
    __termina_box_t __0;
} __option_box_params_t;

/**
 * \brief Structure used to implement the dynamic subtyping relationship.
 */
typedef struct {

    // \brief The current variant.
    __enum_option_t __variant;

    // \brief The parameter of the Somevariant.
    __option_box_params_t Some;

} __option_box_t;

/**
 * \brief Type of the allocator interface.
 */
typedef struct {

    void * __that;
    void (*alloc) (const __termina_event_t * const, void * const, __option_box_t * const);
    void (*free) (const __termina_event_t * const, void * const, __termina_box_t);

} __termina_allocator_t;

typedef struct {

    // \brief Identifier of the target task.
    __termina_id_t task_id;

    // \brief Identifier of the target task's port connected to the channel.
    __termina_id_t port_id;

    // \brief Identifier of the target task's event message queue.
    __termina_id_t task_msg_queue_id;

    // \brief Identifier of the channel message queue.
    __termina_id_t channel_msg_queue_id;

} __termina_msg_queue_t;

typedef __termina_msg_queue_t * __termina_out_port_t;

typedef struct {
    __termina_resource_lock_type_t __lock_type;
} __termina_system_entry_t;

#endif // __TERMINA__TYPES_H__
