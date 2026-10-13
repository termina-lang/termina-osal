#include <termina.h>
#include <termina/shared/except.h>
#include <termina/os/rtems/except.h>
#include <termina/os/rtems/task.h>

#include <rtems.h>

#include <stdint.h>

void termina__os__except__init_emitter(void) {

    // Nothing to do for RTEMS
    return;

}

void termina__rtems__except__stack_overflow(const Thread_Control * running,
                                            bool pattern_ok) {

    (void)pattern_ok;

    termina__except__stack_overflow(
        termina__rtems__task__find_task(running->Object.id));

}

void termina__rtems__except__fatal_extension(
    const rtems_fatal_source source,
    const bool always_set_to_false,
    const rtems_fatal_code code) {

    (void)always_set_to_false;

    // A shutdown is left to the extensions that follow
    if (RTEMS_FATAL_SOURCE_EXIT != source) {

        if (RTEMS_FATAL_SOURCE_EXCEPTION == source) {

            termina__rtems__platform__processor_fault(
                (const CPU_Exception_frame *)code);

        } else {

            termina__except__kernel_failure((uint32_t)source, (size_t)code);

        }

    }

}
