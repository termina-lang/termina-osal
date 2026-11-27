/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Quiescing of the system on RTEMS.
 */

#include <termina.h>
#include <termina/shared/exec.h>

#include <rtems.h>

void termina__os__exec__quiesce(void) {

    rtems_interrupt_level level;

    // Dispatch happens on interrupt exit, so on a single processor disabling
    // the interrupts also stops preemption. The level is not restored, since
    // neither the exception path nor a handover returns.
    rtems_interrupt_local_disable(level);
    (void) level;

}
