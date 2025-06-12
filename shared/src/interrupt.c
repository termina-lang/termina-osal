
#include <termina.h>

#include <termina/shared/interrupt.h>

__termina_shared_interrupt_t __shared_interrupt_table[__TERMINA_NUMBER_OF_INTERRUPTS];

void __termina_interrupt__init(const __termina_id_t interrupt_id,
                               const __termina_id_t emitter_id,
                               const __termina_interrupt_connection_t * const connection,
                               int32_t * const status) {

    *status = 0;

    if (__TERMINA_NUMBER_OF_INTERRUPTS <= interrupt_id) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

        interrupt->emitter_id = emitter_id;
        interrupt->interrupt_id = interrupt_id;
        interrupt->connection = *connection;

        __termina_interrupt_os__init(interrupt_id, status);

    }

    return;

}
