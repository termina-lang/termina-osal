#ifndef TERMINA__SYSTEM_INIT_H__
#define TERMINA__SYSTEM_INIT_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * \brief Dispatches the initial event of the system.
 *
 * Builds the event, reads the uptime, calls the action of the handler the
 * connection names and reports a failing status as an action-failure
 * exception. The application calls it once, from its initialization sequence,
 * at the point that sequence decides: after the message queues, the channels
 * and the pools are up, and before the mutexes, the protection, the emitters,
 * the handlers and the tasks.
 *
 * @param[in] emitter_id  the identifier of the system initialization emitter.
 * @param[in] connection  the handler that attends the event.
 */
void termina__system_init__dispatch(
    const termina__id_t emitter_id,
    const termina__system_init_connection_t * const connection);

#endif // TERMINA__SYSTEM_INIT_H__
