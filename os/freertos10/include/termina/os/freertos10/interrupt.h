/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Dispatch of the interrupts on FreeRTOS and enabling of the interrupt
 *        lines, which each platform implements.
 */

#ifndef TERMINA__OS__FREERTOS10__INTERRUPT_H__
#define TERMINA__OS__FREERTOS10__INTERRUPT_H__

#include <termina/types.h>

/**
 * @brief Dispatches an interrupt to the entity connected to it.
 *
 * The platform calls it from its vector table, with the number already
 * translated to the identifier that Termina uses. The dispatch is the same on
 * any FreeRTOS platform.
 *
 * @param[in] interrupt_id  Identifier of the interrupt that fired.
 */
void termina__freertos__interrupt__dispatch(const termina__id_t interrupt_id);

/**
 * @brief Enables an interrupt line in the interrupt controller of the
 *        platform.
 *
 * Each platform implements this function, since the controller is not part
 * of FreeRTOS: the NVIC on a Cortex-M, another controller on other
 * architectures.
 *
 * @param[in] interrupt_id  Identifier of the interrupt to enable.
 */
void termina__freertos__interrupt__enable(const termina__id_t interrupt_id);

#endif // TERMINA__OS__FREERTOS10__INTERRUPT_H__
