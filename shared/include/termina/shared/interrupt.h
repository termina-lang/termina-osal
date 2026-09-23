#ifndef TERMINA__SHARED__INTERRUPT_H__
#define TERMINA__SHARED__INTERRUPT_H__

#include <termina.h>

typedef struct {

    //! Identifier of the event emitter
    termina__id_t emitter_id;

    //! Interrupt vector/identifier.
    termina__id_t interrupt_id;

    //! Source port of the interrupt event 
    termina__interrupt_connection_t connection;

} termina__shared__interrupt_t;

#ifndef TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS
#error "config.h must define TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS"
#endif

extern termina__shared__interrupt_t termina__shared__interrupt_table[TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS];

/**
 * \brief Initializes an interrupt.
 *        Operating system implementation-dependent function.
 * 
 * @param[in]   interrupt_id  the interrupt identifier/vector.
 */
void termina__interrupt_os__init(const termina__id_t interrupt_id,
                                  int32_t * const status);


#endif // TERMINA__SHARED__INTERRUPT_H__
