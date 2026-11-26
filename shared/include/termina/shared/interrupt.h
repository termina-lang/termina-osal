/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Table of the interrupt emitters and their initialization by the
 *        back-end.
 */

#ifndef TERMINA__SHARED__INTERRUPT_H__
#define TERMINA__SHARED__INTERRUPT_H__

#include "config.h"

#include <termina.h>

/**
 * @brief Interrupt emitter.
 */
typedef struct {

    //! Identifier of the event emitter.
    termina__id_t emitter_id;

    //! Interrupt vector or identifier.
    termina__id_t interrupt_id;

    //! Connection of the interrupt to its task or handler.
    termina__interrupt_connection_t connection;

} termina__shared__interrupt_t;

#ifndef TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS
#error "config.h must define TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS"
#endif

/** @brief Table of the interrupt emitters, indexed by interrupt identifier. */
extern termina__shared__interrupt_t termina__shared__interrupt_object_table[TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS];

/**
 * @brief Installs an interrupt in the operating system.
 * 
 * Each operating system implements this function.
 *
 * @param[in]  interrupt_id  Interrupt identifier or vector.
 * @param[out] status        Status of the operation: `termina__error__none`,
 *                           or the error code of the back-end.
 */
void termina__interrupt_os__init(const termina__id_t interrupt_id,
                                  termina__error_code_t * const status);


#endif // TERMINA__SHARED__INTERRUPT_H__
