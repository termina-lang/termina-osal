
#include <termina.h>

#include <termina/shared/interrupt.h>

termina__shared_interrupt_t __shared_interrupt_table[TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS];

void termina__interrupt__init(const termina__id_t interrupt_id,
                               const termina__id_t emitter_id,
                               const termina__interrupt_connection_t * const connection,
                               int32_t * const status) {

    *status = 0;

    if (TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS <= interrupt_id) {

        *status = -1;

    }

    if (0 == *status) {

        termina__shared_interrupt_t * interrupt = &__shared_interrupt_table[interrupt_id];

        interrupt->emitter_id = emitter_id;
        interrupt->interrupt_id = interrupt_id;
        interrupt->connection = *connection;

        termina__interrupt_os__init(interrupt_id, status);

    }

    return;

}
