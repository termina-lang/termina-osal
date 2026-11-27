/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Fatal errors of FreeRTOS reported as `EKernelFailure`.
 */

#ifndef TERMINA__OS__FREERTOS10__EXCEPT_H__
#define TERMINA__OS__FREERTOS10__EXCEPT_H__

/**
 * @brief Sources of the `EKernelFailure` exception on FreeRTOS.
 *
 * FreeRTOS has no numbering of its own for its fatal errors. The values are
 * part of the interface that a `system_except` handler decodes.
 */
#define TERMINA__FREERTOS__KERNEL_FAILURE__ASSERT 1U /**< An assertion of the kernel failed; the code is the return address of the call that the failed `configASSERT` makes. */

/**
 * @brief Raises `EKernelFailure` when an assertion of the kernel fails;
 *        `configASSERT` calls it.
 */
void termina__freertos__except__assert_failed(void);

#endif // TERMINA__OS__FREERTOS10__EXCEPT_H__
