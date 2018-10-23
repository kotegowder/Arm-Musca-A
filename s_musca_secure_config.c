/*
 * Copyright (c) 2017 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cmsis.h"
#include "Driver_MPC.h"
#include "region_defs.h"
#include "s_ns_shared.h"
#include "s_secure_config.h"

extern ARM_DRIVER_MPC Driver_ISRAM0_MPC;
extern ARM_DRIVER_MPC Driver_ISRAM1_MPC;
extern ARM_DRIVER_MPC Driver_ISRAM2_MPC;
extern ARM_DRIVER_MPC Driver_ISRAM3_MPC;
extern ARM_DRIVER_MPC Driver_SRAM1_MPC;
extern ARM_DRIVER_MPC Driver_QSPI_MPC;

void MPC_config(void)
{
    /* Initialize the MPCs */
    ARM_DRIVER_MPC* mpc_data_region0 = &Driver_ISRAM0_MPC;
    ARM_DRIVER_MPC* mpc_data_region1 = &Driver_ISRAM1_MPC;
    ARM_DRIVER_MPC* mpc_data_region2 = &Driver_ISRAM2_MPC;
    ARM_DRIVER_MPC* mpc_data_region3 = &Driver_ISRAM3_MPC;

#ifdef __USE_FLASH
    /* Configure MPC for QSPI flash
     * This MPC is needed is two cases:
     *  - When the code is loaded to Flash and runs from there
     *  - When the code is loaded to Flash but runs from SRAM.
     *    In this case only the application code gets copied to SRAM,
     *    the library functions and the reset handler will still run from Flash,
     *    so this MPC config is needed
     */
    ARM_DRIVER_MPC* mpc_qspi_code_region = &Driver_QSPI_MPC;
    mpc_qspi_code_region->Initialize();
    mpc_qspi_code_region->ConfigRegion(NS_CODE_START, NS_CODE_LIMIT-1,
                                       ARM_MPC_ATTR_NONSECURE);
    mpc_qspi_code_region->ConfigRegion(S_CODE_START, S_CODE_LIMIT-1,
                                       ARM_MPC_ATTR_SECURE);
    mpc_qspi_code_region->LockDown();

#ifdef __USE_BOTH_CODE_MEMORY
    /* Configure MPC for Code SRAM */
    /* This is only needed if the code runs from SRAM */
    ARM_DRIVER_MPC* mpc_code_region = &Driver_SRAM1_MPC;
    mpc_code_region->Initialize();
    mpc_code_region->ConfigRegion(NS_CODE_SRAM_EXEC_BASE, NS_CODE_SRAM_EXEC_LIMIT-1,
                                  ARM_MPC_ATTR_NONSECURE);
    mpc_code_region->ConfigRegion(S_CODE_SRAM_EXEC_BASE, S_CODE_SRAM_EXEC_LIMIT-1,
                                  ARM_MPC_ATTR_SECURE);
#endif
#else
    /* Configure MPC for Code SRAM */
    ARM_DRIVER_MPC* mpc_code_region = &Driver_SRAM1_MPC;
    mpc_code_region->Initialize();
    mpc_code_region->ConfigRegion(NS_CODE_START, NS_CODE_LIMIT-1,
                                  ARM_MPC_ATTR_NONSECURE);

    mpc_code_region->ConfigRegion(S_CODE_START, S_CODE_LIMIT-1,
                                  ARM_MPC_ATTR_SECURE);
    mpc_code_region->LockDown();
#endif

    /* Configure data memory MPCs */
    mpc_data_region0->Initialize();
    mpc_data_region1->Initialize();
    mpc_data_region2->Initialize();
    mpc_data_region3->Initialize();

    mpc_data_region0->ConfigRegion(MPC_ISRAM0_RANGE_BASE_S, MPC_ISRAM0_RANGE_LIMIT_S,
                                   ARM_MPC_ATTR_SECURE);
    mpc_data_region1->ConfigRegion(MPC_ISRAM1_RANGE_BASE_S, MPC_ISRAM1_RANGE_LIMIT_S,
                                   ARM_MPC_ATTR_SECURE);
    mpc_data_region2->ConfigRegion(MPC_ISRAM2_RANGE_BASE_NS, MPC_ISRAM2_RANGE_LIMIT_NS,
                                   ARM_MPC_ATTR_NONSECURE);
    mpc_data_region3->ConfigRegion(MPC_ISRAM3_RANGE_BASE_NS, MPC_ISRAM3_RANGE_LIMIT_NS,
                                   ARM_MPC_ATTR_NONSECURE);

    mpc_data_region0->LockDown();
    mpc_data_region1->LockDown();
    mpc_data_region2->LockDown();
    mpc_data_region3->LockDown();

}

void SAU_and_IDAU_config(void)
{
    uint32_t sau_region = 0;

    /* Enable SAU */
    TZ_SAU_Enable();

    /* Configures code memory region - can be either Flash or SRAM */
    SAU->RNR  = sau_region;
    SAU->RBAR = (NS_CODE_START & SAU_RLAR_LADDR_Msk);
    SAU->RLAR = ((NS_CODE_LIMIT-1) & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;
    sau_region++;

#ifdef __USE_BOTH_CODE_MEMORY
    SAU->RNR  = sau_region;
    SAU->RBAR = (NS_CODE_SRAM_EXEC_BASE & SAU_RLAR_LADDR_Msk);
    SAU->RLAR = ((NS_CODE_SRAM_EXEC_LIMIT-1) & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;
    sau_region++;
#endif

    SAU->RNR  = sau_region;
    SAU->RBAR = ((NS_DATA_START) & SAU_RLAR_LADDR_Msk);
    SAU->RLAR = ((NS_DATA_LIMIT-1) & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;
    sau_region++;

    SAU->RNR  = sau_region;
    SAU->RBAR = (CMSE_VENEER_REGION_BASE & SAU_RLAR_LADDR_Msk);
    SAU->RLAR = ((CMSE_VENEER_REGION_LIMIT-1) & SAU_RLAR_LADDR_Msk)
                | SAU_RLAR_ENABLE_Msk
                | SAU_RLAR_NSC_Msk;
    sau_region++;

    /* Configures CODE region (0x1000_0000 to 0x1FFF_FFFF)
     * to Non-secure Callable. */
    CMSDK_SPCTRL->nsccfg |= 1;
}



