/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Quiescing of the system on FreeRTOS.
 */

#include <termina.h>
#include <termina/shared/exec.h>

#include <FreeRTOS.h>

void termina__os__exec__quiesce(void) {

    // Disables the interrupts without a nesting count, from a task or from an
    // interrupt handler.
    portDISABLE_INTERRUPTS();

}
