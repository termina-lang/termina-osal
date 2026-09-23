#ifndef TERMINA__OS__FREERTOS10__INTERRUPT_H__
#define TERMINA__OS__FREERTOS10__INTERRUPT_H__

#include <termina/types.h>

/**
 * \brief Dispatches an interrupt to the entity connected to it.
 *
 * The platform calls it from whatever its vector table gives it, with the
 * number already translated to the identifier Termina uses. Everything the
 * dispatch does is the same on any FreeRTOS, which is why it lives here and
 * not beside the vector table.
 *
 * @param[in] interrupt_id  the interrupt that fired.
 */
void termina__freertos__interrupt__dispatch(const termina__id_t interrupt_id);

/**
 * \brief Enables an interrupt line in the controller of the platform.
 *
 * Implemented by each platform, since the controller is not part of FreeRTOS:
 * the NVIC on a Cortex-M, something else elsewhere.
 *
 * @param[in] interrupt_id  the interrupt to enable.
 */
void termina__freertos__interrupt__enable(const termina__id_t interrupt_id);

#endif // TERMINA__OS__FREERTOS10__INTERRUPT_H__
