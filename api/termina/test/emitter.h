#ifndef TERMINA__TEST__EMITTER_H__
#define TERMINA__TEST__EMITTER_H__

#include <termina/types.h>
#include <termina/emitter.h>

/**
 * \brief Type of the function generated for a TestEmitter connected to a
 *        handler, which calls the action of the handler with the value.
 */
typedef void (*termina__test__emitter_handler_action_t)(const termina__event_t * const,
                                                        const void * const);

/**
 * \brief Connection of a TestEmitter to a handler.
 */
typedef struct {

    //! Identifier of the handler
    termina__id_t handler_id;

    //! Function generated for the TestEmitter
    termina__test__emitter_handler_action_t handler_action;

} termina__test__emitter_handler_connection_t;

/**
 * \brief Type of the TestEmitter objects.
 */
typedef struct {

    //! Identifier of the emitter, from 1
    termina__id_t emitter_id;

    union {
        termina__emitter_task_connection_t task;
        termina__test__emitter_handler_connection_t handler;
    };

    termina__emitter_connection_type_t type;

} termina__test__emitter_t;

/**
 * \brief Type of the access ports to a TestEmitter, the same for every type.
 */
typedef struct {

    void * _that;
    void (*fire) (const termina__event_t * const, void * const, const void * const);

} termina__test__emitter_access_t;

/**
 * \brief Fires the emitter with a value.
 *
 * For a task, delivers the event as the real emitter does. For a handler,
 * runs its action at priority 1 and brings the task of the case back to its
 * priority when the action returns.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the TestEmitter object.
 * @param[in]  value          the value of the event.
 */
void termina__test__emitter__fire(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const void * const value);

#endif // TERMINA__TEST__EMITTER_H__
