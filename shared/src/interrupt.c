
#include <termina.h>

#include <termina/shared/interrupt.h>

__termina_shared_interrupt_t __shared_interrupt_table[__TERMINA_NUMBER_OF_INTERRUPTS];

void __termina_interrupt__init(const __termina_id_t interrupt_id,
                               const __termina_interrupt_connection_t * const connection,
                               Status * const status) {

    status->__variant = Status__Success;

    if (__TERMINA_NUMBER_OF_INTERRUPTS <= interrupt_id) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    if (status->__variant == Status__Success) {

        __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

        interrupt->interrupt_id = interrupt_id;
        interrupt->connection = *connection;

        __termina_interrupt_os__init(interrupt_id, status);

    }

    return;

}
