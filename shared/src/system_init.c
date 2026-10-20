#include <termina/system_init.h>

#include <termina/except.h>
#include <termina/system/sys_time.h>

void termina__system_init__dispatch(
    const termina__id_t emitter_id,
    const termina__system_init_connection_t * const connection) {

    TimeVal current;

    termina__event_t event = {
        .emitter_id = emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = connection->handler_id,
        // The handler has a single sink port, so the port is always 0
        .port_id = 0
    };

    SystemEntry__clock_get_uptime(&event, &current);

    connection->handler_action(&event, connection->handler_object, current);

}
