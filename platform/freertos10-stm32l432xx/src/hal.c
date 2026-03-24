/**
 * @file    hal.c
 * @brief   Minimal HAL implementation for STM32L432xx - Termina OSAL
 *
 * Direct register manipulation replacing the full ST HAL drivers.
 * Only the functionality actually used by the platform is implemented.
 */

#include "hal.h"

/* SysTick interrupt priority – lowest on a 4-bit NVIC */
#define TICK_INT_PRIORITY  0x0FU

void __hal_init(void)
{
    /* Flash: I-cache and D-cache are enabled by default after reset.
       Prefetch is disabled by default. No changes needed. */

    /* Set NVIC Priority Grouping to 4 (all preemption bits, no sub-priority).
       PRIGROUP value 3 => 4 bits for preemption, 0 bits for sub-priority. */
    NVIC_SetPriorityGrouping(3U);

    /* Configure SysTick for 1 ms tick at current clock (MSI 4 MHz after reset) */
    SysTick_Config(SystemCoreClock / 1000U);
    NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY);
}

void __hal_system_clock_config(void)
{
    /* ------------------------------------------------------------------ */
    /* MSI configuration – keep at 4 MHz (range 6), switch source to CR   */
    /* ------------------------------------------------------------------ */
    SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);
    MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, RCC_CR_MSIRANGE_6);

    /* Set MSI trimming to default (matches original HAL_Init behaviour) */
    MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, 0U);

    /* ------------------------------------------------------------------ */
    /* PLL configuration – MSI 4 MHz * 40 / 1 / 2 = 80 MHz               */
    /* ------------------------------------------------------------------ */

    /* Disable PLL before reconfiguring */
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != 0U) {}

    /* Write full PLL configuration register.
       PLLSRC  = MSI          (bits [1:0]   = 0x01)
       PLLM    = 1  (val 0)   (bits [6:4]   = 0)
       PLLN    = 40           (bits [14:8]  = 40)
       PLLQ    = 4  (val 1)   (bits [22:21] = 1)
       PLLR    = 2  (val 0)   (bits [26:25] = 0)
       PLLPDIV = 7            (bits [31:27] = 7) */
    WRITE_REG(RCC->PLLCFGR,
              RCC_PLLCFGR_PLLSRC_MSI
            | (0U  << RCC_PLLCFGR_PLLM_Pos)
            | (40U << RCC_PLLCFGR_PLLN_Pos)
            | (1U  << RCC_PLLCFGR_PLLQ_Pos)
            | (0U  << RCC_PLLCFGR_PLLR_Pos)
            | (7U  << RCC_PLLCFGR_PLLPDIV_Pos));

    /* Enable PLL and its SYSCLK output (PLLREN) */
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN);

    /* Wait for PLL lock */
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == 0U) {}

    /* ------------------------------------------------------------------ */
    /* Flash latency – must increase BEFORE switching to faster clock      */
    /* ------------------------------------------------------------------ */
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_4WS);
    while (READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_4WS) {}

    /* ------------------------------------------------------------------ */
    /* System clock switch to PLL                                          */
    /* ------------------------------------------------------------------ */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}

    /* AHB, APB1, APB2 prescalers = /1 (already the default, set explicitly) */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE,  0U);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, 0U);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, 0U);

    /* ------------------------------------------------------------------ */
    /* Update global clock variable and reconfigure SysTick for 80 MHz     */
    /* ------------------------------------------------------------------ */
    SystemCoreClock = 80000000U;

    SysTick_Config(SystemCoreClock / 1000U);
    NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY);
}
