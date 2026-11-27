/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Minimal hardware abstraction layer of the STM32L432xx, which
 *        replaces the ST HAL drivers.
 *
 * It provides only the system initialization, the clock configuration and
 * the NVIC priority grouping.
 */

#ifndef TERMINA__HAL__H
#define TERMINA__HAL__H

#include "stm32l4xx.h"

/**
 * @brief Initializes the hardware by setting the NVIC priority grouping.
 *
 * The NVIC priority grouping is set to 4 (all preemption, no sub-priority).
 * The flash I-cache and D-cache are left enabled and the prefetch disabled,
 * as they are after reset. The function does not configure the SysTick,
 * which FreeRTOS programs from `configCPU_CLOCK_HZ` when the scheduler
 * starts.
 */
void termina__hal__init(void);

/**
 * @brief Configures the system clock to 80 MHz through the PLL fed from the
 *        MSI.
 *
 * MSI at 4 MHz (range 6), PLL with M = 1, N = 40 and R = 2, SYSCLK at 80 MHz.
 * The flash latency is set to 4 wait states, and the AHB, APB1 and APB2
 * prescalers are all set to 1. The function updates `SystemCoreClock` to the
 * new frequency.
 */
void termina__hal__system_clock_config(void);

/**
 * @brief Entry of the vector table for every external interrupt.
 *
 * The function reads the exception number from the IPSR and subtracts the 16
 * system exceptions of the Cortex-M. It hands the resulting interrupt number
 * to `termina__freertos__interrupt__dispatch()`. `startup_stm32l432xx.s` names
 * it.
 */
void termina__hal__generic_handler(void);

/**
 * @brief Entry of the vector table for the SysTick exception.
 *
 * `startup_stm32l432xx.s` names it.
 */
void termina__hal__systick_handler(void);

#endif /* TERMINA__HAL__H */
