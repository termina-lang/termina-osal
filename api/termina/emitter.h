/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Types of the connections of the periodic timers, the interrupts and
 *        the system initialization emitter to the tasks and handlers that
 *        attend them.
 */

#ifndef TERMINA__EMITTER_H__
#define TERMINA__EMITTER_H__

#include <termina/types.h>
#include <termina/msg_queue.h>
#include <termina/prelude.h>

/**
 * @brief Action of a handler that attends a periodic timer, which receives
 *        the current time.
 */
typedef void (*termina__periodic_timer_action_t)(const termina__event_t * const, void * const, const TimeVal);

/**
 * @brief Connection of an emitter to a task.
 */
typedef struct {

    //! Identifier of the task that receives the messages.
    termina__id_t task_id;

    //! Identifier of the single message queue of the receiver.
    termina__id_t task_msg_queue_id;

    //! Identifier of the message queue to which the output port is connected.
    termina__id_t sink_msgq_id;

    //! Identifier of the port to which the message queue is connected.
    termina__id_t sink_port_id;    

} termina__emitter_task_connection_t;

/**
 * @brief Kind of element to which an emitter is connected.
 */
typedef enum {

    termina__emitter_connection_type__task,
    termina__emitter_connection_type__handler

} termina__emitter_connection_type_t;


/**
 * @brief Connection of a periodic timer to a handler.
 * 
 * The connection is specific to the periodic timers because the action of
 * the handler receives the current time as a parameter.
 */
typedef struct {

    //! Pointer to the handler object.
    void * handler_object;

    //! Identifier of the handler.
    termina__id_t handler_id;

    //! Pointer to the handler function.
    termina__periodic_timer_action_t handler_action;

} termina__periodic_timer_handler_connection_t;


/**
 * @brief Connection of a periodic timer to a task or to a handler.
 */
typedef struct {

    union {
        termina__emitter_task_connection_t task;
        termina__periodic_timer_handler_connection_t handler;
    };

    termina__emitter_connection_type_t type;

} termina__periodic_timer_connection_t;


/**
 * @brief Action that attends the initial event of the system.
 *
 * It receives the uptime at the moment the event is dispatched, as the action
 * of a periodic timer does.
 */
typedef void (*termina__system_init_action_t)(const termina__event_t * const, void * const, const TimeVal);


/**
 * @brief Connection of the system initialization emitter to the handler that
 *        attends it.
 *
 * The emitter fires once, before the tasks of the application run, so only a
 * handler can attend it and the connection has no task variant.
 */
typedef struct {

    //! Pointer to the handler object.
    void * handler_object;

    //! Identifier of the handler.
    termina__id_t handler_id;

    //! Pointer to the handler function.
    termina__system_init_action_t handler_action;

} termina__system_init_connection_t;


/**
 * @brief Action of a handler that attends an interrupt, which receives the
 *        interrupt number.
 */
typedef void (*termina__interrupt_action_t)(const termina__event_t * const, void * const, const uint32_t);

/**
 * @brief Connection of an interrupt to a handler.
 */
typedef struct {

    //! Identifier of the handler.
    termina__id_t handler_id;

    //! Pointer to the handler object.
    void * handler_object;

    //! Pointer to the handler function.
    termina__interrupt_action_t handler_action;

} termina__interrupt_handler_connection_t;


/**
 * @brief Connection of an interrupt to a task or to a handler.
 */
typedef struct {

    union {
        termina__emitter_task_connection_t task;
        termina__interrupt_handler_connection_t handler;
    };

    termina__emitter_connection_type_t type;

} termina__interrupt_connection_t;


#endif // TERMINA__EMITTER_H__
