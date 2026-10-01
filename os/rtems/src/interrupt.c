
#include <termina.h>

#include <termina/shared/except.h>
#include <termina/shared/interrupt.h>
#include <termina/shared/msg_queue.h>

#include <rtems.h>
#include <rtems/irq-extension.h>

static void termina__rtems__interrupt__task_connection_handler(void * arg) {

    // We need to send the message to the connected task

    termina__shared__interrupt_t * interrupt = arg;

    uint32_t interrupt_id = interrupt->interrupt_id;

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = interrupt->connection.task.task_id,
        .port_id = interrupt->connection.task.sink_port_id
    };

    termina__shared__msg_queue__deliver(interrupt->connection.task.sink_msgq_id,
                                        &interrupt_id,
                                        interrupt->connection.task.task_msg_queue_id,
                                        &event);

}

static void termina__rtems__interrupt__irq_handler_connection_handler(void * arg) {

    // It is a handler. We need to execute it

    Status__i32 result;
    result._variant = Status__Success;

    termina__shared__interrupt_t * interrupt = arg;

    uint32_t interrupt_id = interrupt->interrupt_id;

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = interrupt->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    result = interrupt->connection.handler.handler_action(&event,
                interrupt->connection.handler.handler_object, interrupt_id);
    
    if (Status__Success != result._variant) {
        termina__shared__except__handler_failure(interrupt->connection.handler.handler_id,
                                                 result.Failure._0);
    }

}

void termina__interrupt_os__init(const termina__id_t interrupt_id,
                                  termina__error_code_t * const status) {

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_object_table[interrupt_id];

    *status = termina__error__none;

    rtems_interrupt_handler new_entry;

    if (termina__emitter_connection_type__task == interrupt->connection.type) {
        new_entry = termina__rtems__interrupt__task_connection_handler;
    } else {
        new_entry = termina__rtems__interrupt__irq_handler_connection_handler;
    }

    // The interrupt identifier is the vector number of the board support
    // package, and the entry of the table goes to the handler as its argument.
    if (rtems_interrupt_handler_install(interrupt_id, "termina",
                                        RTEMS_INTERRUPT_UNIQUE, new_entry,
                                        interrupt) != RTEMS_SUCCESSFUL) {

        *status = termina__error__os_failure;

    }

    return;

}
