
#include <termina.h>

#include <termina/shared/interrupt.h>

termina__shared__interrupt_t termina__shared__interrupt_object_table[TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS];

void termina__interrupt__init(const termina__id_t interrupt_id,
                               const termina__id_t emitter_id,
                               const termina__interrupt_connection_t * const connection,
                               termina__error_code_t * const status) {

    *status = termina__error__none;

    if (TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS <= interrupt_id) {

        *status = termina__error__invalid_id;

    }

    if (termina__error__none == *status) {

        termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_object_table[interrupt_id];

        interrupt->emitter_id = emitter_id;
        interrupt->interrupt_id = interrupt_id;
        interrupt->connection = *connection;

        termina__interrupt_os__init(interrupt_id, status);

    }

    if (termina__error__none != *status) {

        *status = termina__error__interrupt_init;

    }

    return;

}
