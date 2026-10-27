#define ARM_CP15_TEXT_SECTION BSP_START_TEXT_SECTION

#include <bsp.h>
#include <bsp/start.h>
#include <bsp/arm-cp15-start.h>
#include <bsp/arm-a9mpcore-start.h>

// Table of bspstartmmu.c of the xilinx_zynq BSP of RTEMS 6.2, plus the two
// windows of the programmable logic, M_AXI_GP0 and M_AXI_GP1 (UG585, table
// 4-1), which the standalone BSP of Xilinx also maps for every design
BSP_START_DATA_SECTION static const arm_cp15_start_section_config
termina__zynq__mmu_config_table[] = {
    ARMV7_CP15_START_DEFAULT_SECTIONS,
#if defined(RTEMS_SMP)
    {
        .begin = 0xffff0000U,
        .end = 0xffffffffU,
        .flags = ARMV7_MMU_DEVICE
    },
#endif
    {
        .begin = 0x40000000U,
        .end = 0xc0000000U,
        .flags = ARMV7_MMU_DEVICE
    }, {
        .begin = 0xe0000000U,
        .end = 0xe0200000U,
        .flags = ARMV7_MMU_DEVICE
    }, {
        .begin = 0xf8000000U,
        .end = 0xf9000000U,
        .flags = ARMV7_MMU_DEVICE
    }
};

// Replaces the weak definition of the BSP
BSP_START_TEXT_SECTION void zynq_setup_mmu_and_cache(void) {

    uint32_t ctrl = arm_cp15_start_setup_mmu_and_cache(
        ARM_CP15_CTRL_A,
        ARM_CP15_CTRL_AFE | ARM_CP15_CTRL_Z
    );

    arm_cp15_start_setup_translation_table_and_enable_mmu_and_cache(
        ctrl,
        // A linker symbol, the origin of the RAM_MMU region of linkcmds
        (uint32_t *) (uintptr_t) bsp_translation_table_base,
        ARM_MMU_DEFAULT_CLIENT_DOMAIN,
        &termina__zynq__mmu_config_table[0],
        RTEMS_ARRAY_SIZE(termina__zynq__mmu_config_table)
    );

}
