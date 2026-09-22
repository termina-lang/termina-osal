#ifndef TERMINA__EMITTER_H__
#define TERMINA__EMITTER_H__

#include <termina/types.h>
#include <termina/msg_queue.h>
#include <termina/prelude.h>

typedef Status__i32 (*termina__periodic_timer_action_t)(const termina__event_t * const, void * const, const TimeVal);

typedef struct {

    // \brief Identifier of the task that will receive the messages
    termina__id_t task_id;

    // \brief Identifier of the single message queue of the receiver
    termina__id_t task_msg_queue_id;

    // \brief Identifier of message queue to which the output port is connected
    termina__id_t sink_msgq_id;

    // \brief Identifier of the port to which the message queue is connected
    termina__id_t sink_port_id;    

} termina__emitter_task_connection_t;

typedef enum {

    termina__emitter_connection_type__task,
    termina__emitter_connection_type__handler

} termina__emitter_connection_type_t;


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
    termina__id_t handler_id;

    //! Pointer to the handler function
    termina__periodic_timer_action_t handler_action;

} termina__periodic_timer_handler_connection_t;


typedef struct {

    union {
        termina__emitter_task_connection_t task;
        termina__periodic_timer_handler_connection_t handler;
    };

    termina__emitter_connection_type_t type;

} termina__periodic_timer_connection_t;


/**
 * \brief Action that attends the initial event of the system.
 *
 * It receives the uptime at the moment the event is dispatched, as the action
 * of a periodic timer does.
 */
typedef Status__i32 (*termina__system_init_action_t)(const termina__event_t * const, void * const, const TimeVal);


/**
 * \brief Connection of the system initialization emitter to the handler that
 *        attends it.
 *
 * The emitter fires once, before the tasks of the application run, so only a
 * handler can attend it and the connection has no task arm.
 */
typedef struct {

    //! Pointer to the handler object
    void * handler_object;

    //! Identifier of the handler
    termina__id_t handler_id;

    //! Pointer to the handler function
    termina__system_init_action_t handler_action;

} termina__system_init_connection_t;


typedef Status__i32 (*termina__interrupt_action_t)(const termina__event_t * const, void * const, const uint32_t);

typedef struct {

    //! Identifier of the handler
    termina__id_t handler_id;

    //! Pointer to the handler object
    void * handler_object;

    //! Pointer to the handler function
    termina__interrupt_action_t handler_action;

} termina__interrupt_handler_connection_t;


typedef struct {

    union {
        termina__emitter_task_connection_t task;
        termina__interrupt_handler_connection_t handler;
    };

    termina__emitter_connection_type_t type;

} termina__interrupt_connection_t;


#endif // TERMINA__EMITTER_H__
