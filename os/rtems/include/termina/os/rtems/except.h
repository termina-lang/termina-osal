#ifndef TERMINA__OS__RTEMS__EXCEPT_H__
#define TERMINA__OS__RTEMS__EXCEPT_H__

#include <termina.h>

#include <rtems.h>

/**
 * \brief Raises EProcessorFault from the exception frame that RTEMS passes
 *        with a fatal error of source RTEMS_FATAL_SOURCE_EXCEPTION.
 *
 * The frame belongs to the CPU port of RTEMS, so each platform implements it.
 *
 * @param[in] frame  The exception frame.
 */
_Noreturn void termina__rtems__platform__processor_fault(
    const CPU_Exception_frame * const frame);

/**
 * \brief Fatal extension of RTEMS, registered as an initial extension.
 */
void termina__rtems__except__fatal_extension(rtems_fatal_source source,
                                             bool always_set_to_false,
                                             rtems_fatal_code code);

#endif // TERMINA__OS__RTEMS__EXCEPT_H__
