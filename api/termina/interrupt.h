#ifndef TERMINA__INTERRUPT_H__
#define TERMINA__INTERRUPT_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * \brief Initializes an interrupt emitter.
 * 
 * @param[in]   timer_id    the identifier of the interrupt emitter.
 * @param[in]   emitter_id  the identifier of the emitter.
 * @param[in]   connection  the connection of the emitter.
 * @param[out]  status      the status of the operation.
 */
void termina__interrupt__init(const termina__id_t irq_emitter_id,
                               const termina__id_t emitter_id,
                               const termina__interrupt_connection_t * const connection,
                               int32_t * const status);


#endif // TERMINA__INTERRUPT_H__
