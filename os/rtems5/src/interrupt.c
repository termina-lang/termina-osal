
#include <termina.h>

#include <termina/shared/interrupt.h>

#include <rtems.h>

rtems_isr __rtems_interrupt__task_connection_handler(rtems_vector_number raw_irq_vector) {

    __termina_id_t interrupt_id = raw_irq_vector - 0x10;

    // We need to send the message to the connected task

    int32_t status = 0;

    __termina_interrupt_connection_t * connection = 
            __termina_shared_interrupt__get_connection(interrupt_id);

    __termina_msg_queue__send(connection->task.sink_msgq_id,
                              &interrupt_id, &status);

    if (0 == status) {

        // Notify the task that a message has been sent
        __termina_msg_queue__send(connection->task.task_msg_queue_id,
                                  &connection->task.sink_port_id, &status);

    }

}

rtems_isr __rtems_interrupt__handler_connection_handler(rtems_vector_number raw_irq_vector) {

    __termina_id_t interrupt_id = raw_irq_vector - 0x10;

    // It is a handler. We need to execute it

    __status_int32_t result;
    result.__variant = Success;

    __termina_interrupt_connection_t * connection = 
            __termina_shared_interrupt__get_connection(interrupt_id);

    result = connection->handler.handler_action(
                connection->handler.handler_object, interrupt_id);
    
    if (Success != result.__variant) {
        __termina_exec__shutdown();
    }

}

void __termina_interrupt_os__init(const __termina_id_t interrupt_id,
                                  int32_t * const status) {

    __termina_interrupt_connection_t * connection = __termina_shared_interrupt__get_connection(interrupt_id);

    *status = 0;

    rtems_isr_entry old_entry;
    rtems_isr_entry new_entry;

    rtems_vector_number raw_irq_vector = interrupt_id + 0x10;

    if (__TerminaEmitterConnectionType__Task == connection->type) {
        new_entry = __rtems_interrupt__task_connection_handler;
    } else {
        new_entry = __rtems_interrupt__handler_connection_handler;
    }

    rtems_interrupt_catch(new_entry, raw_irq_vector, &old_entry);

    return;

}
