
#include <termina.h>

#include <termina/shared/interrupt.h>

#include <rtems.h>
#include <bsp.h>
#include <bsp/irq.h>

rtems_isr __rtems_interrupt__task_connection_handler(rtems_vector_number raw_irq_vector) {

    __termina_id_t interrupt_id = raw_irq_vector - 0x10;

    // We need to send the message to the connected task

    int32_t status = 0;

    __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

    __termina_event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = __termina_active_entity__task,
        .owner.task.task_id = interrupt->connection.task.task_id,
        .port_id = interrupt->connection.task.sink_port_id 
    };

    __termina_msg_queue__send(interrupt->connection.task.sink_msgq_id,
                              &interrupt_id, &status);

    if (0 == status) {

        // Notify the task that a message has been sent
        __termina_msg_queue__send(interrupt->connection.task.task_msg_queue_id,
                                  &event, &status);

    }

}

rtems_isr __rtems_interrupt__handler_connection_handler(rtems_vector_number raw_irq_vector) {

    __termina_id_t interrupt_id = raw_irq_vector - 0x10;

    // It is a handler. We need to execute it

    __status_int32_t result;
    result.__variant = Success;

    __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

    __termina_event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = __termina_active_entity__handler,
        .owner.handler.handler_id = interrupt->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    result = interrupt->connection.handler.handler_action(&event,
                interrupt->connection.handler.handler_object, interrupt_id);
    
    if (Success != result.__variant) {
        __termina_exec__reboot();
    }

}

void __termina_interrupt_os__init(const __termina_id_t interrupt_id,
                                  int32_t * const status) {

    __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

    *status = 0;

    rtems_isr_entry new_entry;

    rtems_vector_number raw_irq_vector = interrupt_id + 0x10;

    if (__termina_emitter_connection_type__task == interrupt->connection.type) {
        new_entry = __rtems_interrupt__task_connection_handler;
    } else {
        new_entry = __rtems_interrupt__handler_connection_handler;
    }

    set_vector(new_entry, raw_irq_vector, 2);

    return;

}
