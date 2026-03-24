/**
 * @file    hal.h
 * @brief   Minimal HAL for STM32L432xx - Termina OSAL
 *
 * Consolidated hardware abstraction replacing the ST HAL drivers.
 * Provides only what is needed: system init, clock configuration,
 * SysTick setup, and NVIC priority grouping.
 */

#ifndef __HAL_H
#define __HAL_H

#include "stm32l4xx.h"

/**
 * @brief  Initialize hardware: NVIC priority grouping and SysTick.
 *
 * Flash I-cache and D-cache are left at their default-enabled state.
 * Prefetch is left disabled (default).
 * NVIC priority grouping is set to 4 (all preemption, no sub-priority).
 * SysTick is configured for 1 ms period at the current SystemCoreClock.
 */
void __hal_init(void);

/**
 * @brief  Configure system clock to 80 MHz via PLL fed from MSI.
 *
 * MSI @ 4 MHz (range 6) -> PLL (M=1, N=40, R=2) -> SYSCLK = 80 MHz.
 * Flash latency is set to 4 WS. AHB/APB1/APB2 prescalers are all /1.
 * SysTick is reconfigured for the new clock frequency.
 */
void __hal_system_clock_config(void);

#endif /* __HAL_H */
