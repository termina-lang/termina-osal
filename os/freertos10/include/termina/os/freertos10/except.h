#ifndef TERMINA__OS__FREERTOS10__EXCEPT_H__
#define TERMINA__OS__FREERTOS10__EXCEPT_H__

/**
 * \brief Sources of the EKernelFailure exception on FreeRTOS, which has no
 *        numbering of its own for its fatal errors. The values are part of
 *        the interface that a system_except handler decodes.
 */
#define TERMINA__FREERTOS__KERNEL_FAILURE__ASSERT 1U /**< An assertion of the kernel failed; the code is the address of the assertion. */

/**
 * \brief Called by configASSERT when an assertion of the kernel fails.
 */
void termina__freertos__except__assert_failed(void);

#endif // TERMINA__OS__FREERTOS10__EXCEPT_H__
