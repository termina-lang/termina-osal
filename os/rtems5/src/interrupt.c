
#include <termina.h>

#include <termina/shared/interrupt.h>

#include <rtems.h>
#include <bsp.h>
#include <bsp/irq.h>

static rtems_isr termina__rtems__interrupt__task_connection_handler(rtems_vector_number raw_irq_vector) {

    uint32_t interrupt_id = raw_irq_vector - 0x10;

    // We need to send the message to the connected task

    int32_t status = 0;

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_table[interrupt_id];

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = interrupt->connection.task.task_id,
        .port_id = interrupt->connection.task.sink_port_id 
    };

    termina__msg_queue__send(interrupt->connection.task.sink_msgq_id,
                              &interrupt_id, &status);

    if (0 == status) {

        // Notify the task that a message has been sent
        termina__msg_queue__send(interrupt->connection.task.task_msg_queue_id,
                                  &event, &status);

    }

}

static rtems_isr termina__rtems__interrupt__irq_handler_connection_handler(rtems_vector_number raw_irq_vector) {

    uint32_t interrupt_id = raw_irq_vector - 0x10;

    // It is a handler. We need to execute it

    Status__i32 result;
    result._variant = Status__Success;

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_table[interrupt_id];

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = interrupt->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    result = interrupt->connection.handler.handler_action(&event,
                interrupt->connection.handler.handler_object, interrupt_id);
    
    if (Status__Success != result._variant) {
        termina__exec__reboot();
    }

}

void termina__interrupt_os__init(const termina__id_t interrupt_id,
                                  int32_t * const status) {

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_table[interrupt_id];

    *status = 0;

    rtems_isr_entry new_entry;

    rtems_vector_number raw_irq_vector = interrupt_id + 0x10;

    if (termina__emitter_connection_type__task == interrupt->connection.type) {
        new_entry = termina__rtems__interrupt__task_connection_handler;
    } else {
        new_entry = termina__rtems__interrupt__irq_handler_connection_handler;
    }

    set_vector(new_entry, raw_irq_vector, 2);

    return;

}
