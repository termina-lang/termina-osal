#ifndef __TERMINA__SHARED__INTERRUPT_H__
#define __TERMINA__SHARED__INTERRUPT_H__

#include <termina.h>

typedef struct {

    //! Interrupt vector/identifier.
    __termina_id_t interrupt_id;

    //! Source port of the interrupt event 
    __termina_interrupt_connection_t connection;

} __termina_shared_interrupt_t;

extern __termina_shared_interrupt_t __shared_interrupt_table[__TERMINA_NUMBER_OF_INTERRUPTS];

/**
 * \brief Initializes an interrupt.
 *        Operating system implementation-dependent function.
 * 
 * @param[in]   interrupt_id  the interrupt identifier/vector.
 */
void __termina_interrupt_os__init(const __termina_id_t timer_id,
                                  int32_t * const status);

/**
 * \brief Gets an interrupt connection from the interrupt identifier.
 * 
 * @param[in] interrupt_id the interrupt identifier.
 * 
 * @return the mutex object.
 */
static inline __termina_interrupt_connection_t * __termina_shared_interrupt__get_connection(
    const __termina_id_t interrupt_id) {

    return &__shared_interrupt_table[interrupt_id].connection;

}

#endif // __TERMINA__SHARED__INTERRUPT_H__
