/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Minimal hardware abstraction layer of the STM32L432xx, which
 *        replaces the ST HAL drivers.
 *
 * It provides only the system initialization, the clock configuration, the
 * SysTick setup and the NVIC priority grouping.
 */

#ifndef TERMINA__HAL__H
#define TERMINA__HAL__H

#include "stm32l4xx.h"

/**
 * @brief Initializes the hardware: NVIC priority grouping and SysTick.
 *
 * The flash I-cache and D-cache are left enabled, as they are by default, and
 * the prefetch is left disabled, also the default. The NVIC priority grouping
 * is set to 4 (all preemption, no sub-priority). The SysTick is configured
 * for a 1 ms period at the current `SystemCoreClock`.
 */
void termina__hal__init(void);

/**
 * @brief Configures the system clock to 80 MHz through the PLL fed from the
 *        MSI.
 *
 * MSI at 4 MHz (range 6), PLL with M = 1, N = 40 and R = 2, SYSCLK at 80 MHz.
 * The flash latency is set to 4 wait states, and the AHB, APB1 and APB2
 * prescalers are all set to 1. The SysTick is reconfigured for the new clock
 * frequency.
 */
void termina__hal__system_clock_config(void);

/**
 * @brief Entry of the vector table for every external interrupt.
 *
 * The function reads the exception number that the CPU left in the IPSR and
 * hands the interrupt to the dispatcher of the port. `startup_stm32l432xx.s`
 * names it.
 */
void termina__hal__generic_handler(void);

/**
 * @brief Entry of the vector table for the SysTick exception.
 *
 * `startup_stm32l432xx.s` names it.
 */
void termina__hal__systick_handler(void);

#endif /* TERMINA__HAL__H */
