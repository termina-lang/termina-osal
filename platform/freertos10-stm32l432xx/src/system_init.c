/**
 * @file    system_init.c
 * @brief   CMSIS Cortex-M4 system initialisation for STM32L432xx
 *
 * Replaces the ST-provided system_stm32l4xx.c.
 * Provides __hal_system_init (called from Reset_Handler before main)
 * and __hal_system_core_clock_update.
 */

#include "stm32l4xx.h"

#if !defined(HSE_VALUE)
#define HSE_VALUE  8000000U
#endif

#if !defined(MSI_VALUE)
#define MSI_VALUE  4000000U
#endif

#if !defined(HSI_VALUE)
#define HSI_VALUE  16000000U
#endif

#define VECT_TAB_OFFSET  0x00U

/* ---- CMSIS-required global variables ---- */

uint32_t SystemCoreClock = 4000000U;

const uint8_t  AHBPrescTable[16] = {
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U
};
const uint8_t  APBPrescTable[8] = {
    0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U
};
const uint32_t MSIRangeTable[12] = {
    100000U,   200000U,   400000U,   800000U,
    1000000U,  2000000U,  4000000U,  8000000U,
    16000000U, 24000000U, 32000000U, 48000000U
};

/**
 * @brief  Early system initialisation (called from Reset_Handler).
 *
 * Enables the FPU, resets the RCC clock tree to MSI 4 MHz defaults,
 * and sets the vector table base address.
 */
void __hal_system_init(void)
{
    /* FPU: enable CP10 and CP11 full access */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
#endif

    /* Reset RCC clock configuration to default (MSI 4 MHz) */
    SET_BIT(RCC->CR, RCC_CR_MSION);
    RCC->CFGR = 0x00000000U;
    RCC->CR &= 0xEAF6FFFFU;        /* Clear HSEON, CSSON, HSION, PLLON */
    RCC->PLLCFGR = 0x00001000U;    /* Reset PLL configuration */
    RCC->CR &= 0xFFFBFFFFU;        /* Clear HSEBYP */
    RCC->CIER = 0x00000000U;       /* Disable all RCC interrupts */

    /* Vector table relocation */
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;
}

/**
 * @brief  Update SystemCoreClock from the current RCC register state.
 */
void __hal_system_core_clock_update(void)
{
    uint32_t tmp, msirange, pllvco, pllr, pllsource, pllm;

    /* Determine MSI range */
    if (READ_BIT(RCC->CR, RCC_CR_MSIRGSEL) == 0U)
    {
        msirange = (RCC->CSR & RCC_CSR_MSISRANGE) >> 8U;
    }
    else
    {
        msirange = (RCC->CR & RCC_CR_MSIRANGE) >> 4U;
    }
    msirange = MSIRangeTable[msirange];

    /* Determine SYSCLK source */
    switch (RCC->CFGR & RCC_CFGR_SWS)
    {
    case 0x00U: /* MSI */
        SystemCoreClock = msirange;
        break;

    case 0x04U: /* HSI */
        SystemCoreClock = HSI_VALUE;
        break;

    case 0x08U: /* HSE */
        SystemCoreClock = HSE_VALUE;
        break;

    case 0x0CU: /* PLL */
        pllsource = RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC;
        pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> 4U) + 1U;

        switch (pllsource)
        {
        case 0x02U: /* HSI */
            pllvco = HSI_VALUE / pllm;
            break;
        case 0x03U: /* HSE */
            pllvco = HSE_VALUE / pllm;
            break;
        default:    /* MSI */
            pllvco = msirange / pllm;
            break;
        }

        pllvco *= (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 8U;
        pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 25U) + 1U) * 2U;
        SystemCoreClock = pllvco / pllr;
        break;

    default:
        SystemCoreClock = msirange;
        break;
    }

    /* Apply AHB prescaler */
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4U)];
    SystemCoreClock >>= tmp;
}
