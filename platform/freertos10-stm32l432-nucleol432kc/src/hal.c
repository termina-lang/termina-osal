/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Minimal hardware abstraction layer of the STM32L432xx, implemented
 *        by direct register access.
 *
 * It replaces the ST HAL drivers and implements only what the platform uses.
 */

#include "hal.h"

/* SysTick interrupt priority, the lowest on a 4-bit NVIC. */
#define TICK_INT_PRIORITY  0x0FU

void termina__hal__init(void)
{
    /* Flash: I-cache and D-cache are enabled by default after reset.
       Prefetch is disabled by default. No changes needed. */

    /* Set NVIC Priority Grouping to 4 (all preemption bits, no sub-priority).
       PRIGROUP value 3 => 4 bits for preemption, 0 bits for sub-priority. */
    NVIC_SetPriorityGrouping(3U);

}

void termina__hal__system_clock_config(void)
{
    /* ------------------------------------------------------------------ */
    /* MSI configuration, 4 MHz (range 6), with the range taken from CR   */
    /* ------------------------------------------------------------------ */
    SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);
    MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, RCC_CR_MSIRANGE_6);

    /* Sets the MSI trimming to its reset value. */
    MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, 0U);

    /* ------------------------------------------------------------------ */
    /* PLL configuration, MSI 4 MHz * 40 / 1 / 2 = 80 MHz                 */
    /* ------------------------------------------------------------------ */

    /* Disables the PLL before reconfiguring it. */
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != 0U) {}

    /* Writes the whole PLL configuration register.
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

    /* Enables the PLL and its SYSCLK output (PLLREN). */
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN);

    /* Waits for the PLL to lock. */
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == 0U) {}

    /* ------------------------------------------------------------------ */
    /* Flash latency, raised before the switch to the faster clock        */
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
    /* Update of the global clock variable                                */
    /* ------------------------------------------------------------------ */
    SystemCoreClock = 80000000U;

}
