#ifndef __TERMINA__EMITTER_H__
#define __TERMINA__EMITTER_H__

#include <termina/types.h>
#include <termina/msg_queue.h>
#include <termina/prelude.h>

typedef __status_int32_t (*__termina_periodic_timer_action_t)(void * const, const TimeVal);

typedef struct {

    // \brief Identifier of the single message queue of the receiver
    __termina_id_t task_msg_queue_id;

    // \brief Identifier of message queue to which the output port is connected
    __termina_id_t sink_msgq_id;

    // \brief Identifier of the port to which the message queue is connected
    __termina_id_t sink_port_id;    

} __termina_emitter_task_connection_t;

typedef enum {

    __TerminaEmitterConnectionType__Task,
    __TerminaEmitterConnectionType__Handler

} __termina_emitter_connection_type_t;


/**
 * \brief Structure that represents a connection of a periodic timer to
 *        to a handler.
 * 
 * This structure is used to connect a periodic timer to a handler function.
 * It has to be specialized because the handler function is specific to the
 * periodic timer connection (i.e., it receives the current time as a parameter).
 */
typedef struct {

    //! Pointer to the handler object
    void * handler_object;

    //! Identifier of the handler
    __termina_id_t handler_id;

    //! Pointer to the handler function
    __termina_periodic_timer_action_t handler_action;

} __termina_periodic_timer_handler_connection_t;


typedef struct {

    union {
        __termina_emitter_task_connection_t task;
        __termina_periodic_timer_handler_connection_t handler;
    };

    __termina_emitter_connection_type_t type;

} __termina_periodic_timer_connection_t;


typedef __status_int32_t (*__termina_interrupt_action_t)(void * const, const uint32_t);

typedef struct {

    //! Pointer to the handler object
    void * handler_object;

    //! Pointer to the handler function
    __termina_interrupt_action_t handler_action;

} __termina_interrupt_handler_connection_t;


typedef struct {

    union {
        __termina_emitter_task_connection_t task;
        __termina_interrupt_handler_connection_t handler;
    };

    __termina_emitter_connection_type_t type;

} __termina_interrupt_connection_t;


#endif // __TERMINA__EMITTER_H__
