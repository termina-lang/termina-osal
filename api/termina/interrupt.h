/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Interface of the interrupt emitters.
 */

#ifndef TERMINA__INTERRUPT_H__
#define TERMINA__INTERRUPT_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * @brief Initializes an interrupt emitter.
 * 
 * @param[in]   interrupt_id  Identifier of the interrupt.
 * @param[in]   emitter_id    Identifier of the emitter.
 * @param[in]   connection    Connection of the emitter.
 * @param[out]  status        Status of the operation: `termina__error__none`,
 *                            or `termina__error__interrupt_init` if the
 *                            identifier is out of range or the interrupt
 *                            cannot be installed.
 */
void termina__interrupt__init(const termina__id_t interrupt_id,
                               const termina__id_t emitter_id,
                               const termina__interrupt_connection_t * const connection,
                               termina__error_code_t * const status);


#endif // TERMINA__INTERRUPT_H__
