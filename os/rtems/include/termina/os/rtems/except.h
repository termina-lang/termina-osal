/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Fatal errors, processor faults and stack overflows of RTEMS reported
 *        as exceptions of the system.
 */

#ifndef TERMINA__OS__RTEMS__EXCEPT_H__
#define TERMINA__OS__RTEMS__EXCEPT_H__

#include <termina.h>

#include <rtems.h>
#include <rtems/score/thread.h>

/**
 * @brief Raises `EProcessorFault` from the exception frame that RTEMS passes
 *        with a fatal error of source `RTEMS_FATAL_SOURCE_EXCEPTION`.
 *
 * The frame belongs to the CPU port of RTEMS, so each platform implements
 * this function.
 *
 * @param[in] frame  Exception frame.
 */
_Noreturn void termina__rtems__platform__processor_fault(
    const CPU_Exception_frame * const frame);

/**
 * @brief Reporter of the stack checker of RTEMS, which raises
 *        `EStackOverflow` with the task whose stack overflowed.
 *
 * @param[in] running     Thread whose stack overflowed.
 * @param[in] pattern_ok  Whether the stack pattern is intact; unused.
 */
void termina__rtems__except__stack_overflow(const Thread_Control * running,
                                            bool pattern_ok);

/**
 * @brief Fatal extension of RTEMS, registered as an initial extension.
 *
 * A fatal error of source `RTEMS_FATAL_SOURCE_EXCEPTION` raises
 * `EProcessorFault`, and any other raises `EKernelFailure`.
 *
 * @param[in] source               Source of the fatal error.
 * @param[in] always_set_to_false  Unused.
 * @param[in] code                 Code of the fatal error.
 */
void termina__rtems__except__fatal_extension(rtems_fatal_source source,
                                             bool always_set_to_false,
                                             rtems_fatal_code code);

#endif // TERMINA__OS__RTEMS__EXCEPT_H__
