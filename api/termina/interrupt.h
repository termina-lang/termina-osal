#ifndef __TERMINA__INTERRUPT_H__
#define __TERMINA__INTERRUPT_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * \brief Initializes an interrupt emitter.
 * 
 * @param[in]   timer_id    the identifier of the interrupt emitter.
 * @param[in]   connection  the connection of the emitter.
 * @param[out]  status      the status of the operation.
 */
void __termina_interrupt__init(const __termina_id_t irq_emitter_id,
                               const __termina_interrupt_connection_t * const connection,
                               Status * const status);


#endif // __TERMINA__INTERRUPT_H__
