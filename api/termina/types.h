#ifndef __TERMINA__TYPES_H__
#define __TERMINA__TYPES_H__

#include <stdint.h>
#include <stddef.h>

/**
 * \brief Type of the Termina object identifiers.
 */
typedef size_t __termina_id_t;

#define __TERMINA_ID_INVALID SIZE_MAX

/**
 * \brief Type of the pool global objects.
 */
typedef struct {

    __termina_id_t __pool_id;

    __termina_id_t __mutex_id;

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
    void (*alloc) (void * const, __option_box_t * const);
    void (*free) (void * const, __termina_box_t);

} __termina_allocator_t;

typedef struct {

    __termina_id_t task_msg_queue_id;

    __termina_id_t channel_msg_queue_id;

    __termina_id_t port_id;

} __termina_msg_queue_t;

typedef __termina_msg_queue_t * __termina_out_port_t;

#endif // __TERMINA__TYPES_H__
