/*
 * Copyright (c) 2017 ARM Limited
 *
 * Licensed under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ARM_LTD_DEVICE_CFG_H__
#define __ARM_LTD_DEVICE_CFG_H__

/**
 * \file device_cfg.h
 * \brief
 * This is the default device configuration file with all peripherals
 * defined and configured to be use via the non-secure base address.
 * This file is an example of how to define your own configuration file
 * with the peripherals required for your application.
 */

/* ARM SCC */
#define ARM_SCC_S
#define ARM_SCC_NS

/* ARM GPIO */
#define ARM_GPIO0_S
#define ARM_GPIO0_NS

/* ARM Memory Protection Controller (MPC) SIE 200 */
#define MPC_ISRAM0_S
#define MPC_ISRAM1_S
#define MPC_ISRAM2_S
#define MPC_ISRAM3_S
#define MPC_CODE_SRAM1_S
#define MPC_CODE_SRAM1_NS
#define MPC_QSPI_S
#define MPC_QSPI_NS

/* ARM Message Handler Units (MHU) */
#define ARM_MHU0_S
#define ARM_MHU0_NS
#define ARM_MHU1_S
#define ARM_MHU1_NS

/*ARM UART Controller PL011*/
#define UART0_PL011_S
#define UART0_PL011_NS
#define UART1_PL011_S
#define UART1_PL011_NS

/* APB Dualtimers */
#define CMSDK_DUALTIMER_S
#define CMSDK_DUALTIMER_NS

/* CMSDK Timers */
#define CMSDK_TIMER0_S
#define CMSDK_TIMER0_NS
#define CMSDK_TIMER1_S
#define CMSDK_TIMER1_NS

#endif  /* __ARM_LTD_DEVICE_CFG_H__ */
