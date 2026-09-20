
#include <termina.h>

#include <termina/shared/interrupt.h>

#include "FreeRTOSConfig.h"
#include "stm32l432xx.h"

typedef void (*__freertos_interrupt_handler_t)(const termina__id_t interrupt_id);

static __freertos_interrupt_handler_t interrupt_handlers[TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS];

void __freertos_interrupt__task_connection_handler(const termina__id_t interrupt_id) {

    // We need to send the message to the connected task

    int32_t status = 0;

    termina__shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

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

void __freertos_interrupt__irq_handler_connection_handler(const termina__id_t interrupt_id) {

    // It is a handler. We need to execute it

    Status__i32 result;
    result._variant = Status__Success;

    termina__shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

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

    termina__shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

    *status = 0;

    if (termina__emitter_connection_type__task == interrupt->connection.type) {
        interrupt_handlers[interrupt_id] = __freertos_interrupt__task_connection_handler;
    } else {
        interrupt_handlers[interrupt_id] = __freertos_interrupt__irq_handler_connection_handler;
    }

    // Habilitar la interrupción en el NVIC
    NVIC_SetPriority((IRQn_Type)interrupt_id, 
                     configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ((IRQn_Type)interrupt_id);

    return;

}

void __hal_generic_handler(void) {

    uint32_t irq = (__get_IPSR() & 0x1FF) - 16;

    if (irq < TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS && interrupt_handlers[irq] != NULL) {
        interrupt_handlers[irq](irq);
    } else {
        // No handler registered for this interrupt, reboot the system
        termina__exec__reboot();
    }

}