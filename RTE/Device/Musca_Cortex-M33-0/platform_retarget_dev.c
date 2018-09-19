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

/**
 * \file platform_retarget_dev.c
 * \brief This file defines exports the structures based on the peripheral
 * definitions from device_cfg.h.
 * This retarget file is meant to be used as a helper for baremetal
 * applications and/or as an example of how to configure the generic
 * driver structures.
 */

#include "platform_retarget_dev.h"
#include "platform_retarget.h"
#include "system_cmsdk_musca.h"

/* ======= Peripheral configuration structure definitions ======= */
/* ARM SCC driver structures */
#ifdef ARM_SCC_S
static const struct arm_scc_dev_cfg_t ARM_SCC_DEV_CFG_S = {
    .base = MUSCA_SCC_S_BASE};
struct arm_scc_dev_t ARM_SCC_DEV_S = {&(ARM_SCC_DEV_CFG_S)};
#endif
#ifdef ARM_SCC_NS
static const struct arm_scc_dev_cfg_t ARM_SCC_DEV_CFG_NS = {
    .base = MUSCA_SCC_NS_BASE};
struct arm_scc_dev_t ARM_SCC_DEV_NS = {&(ARM_SCC_DEV_CFG_NS)};
#endif

/* ARM GPIO driver structures */
#ifdef ARM_GPIO0_S
#ifndef ARM_SCC_S
#error "SCC is needed for GPIO"
#endif
static const struct arm_gpio_dev_cfg_t ARM_GPIO0_DEV_CFG_S = {
    .base = MUSCA_GPIO_S_BASE,
    .scc_dev = (uint32_t)&ARM_SCC_DEV_S};
static struct arm_gpio_dev_data_t ARM_GPIO0_DEV_DATA_S = {
    .state = ARM_GPIO_UNINITIALIZED,
    .port_mask = DEFAULT_PORT_MASK};
struct arm_gpio_dev_t ARM_GPIO0_DEV_S = {&(ARM_GPIO0_DEV_CFG_S),
                                         &(ARM_GPIO0_DEV_DATA_S)};
#endif
#ifdef ARM_GPIO0_NS
#ifndef ARM_SCC_NS
#error "SCC is needed for GPIO"
#endif
static const struct arm_gpio_dev_cfg_t ARM_GPIO0_DEV_CFG_NS = {
    .base = MUSCA_GPIO_NS_BASE,
    .scc_dev = (uint32_t)&ARM_SCC_DEV_NS};
static struct arm_gpio_dev_data_t ARM_GPIO0_DEV_DATA_NS = {
    .state = ARM_GPIO_UNINITIALIZED,
    .port_mask = DEFAULT_PORT_MASK};
struct arm_gpio_dev_t ARM_GPIO0_DEV_NS = {&(ARM_GPIO0_DEV_CFG_NS),
                                          &(ARM_GPIO0_DEV_DATA_NS)};
#endif

/* ARM MPC SIE 200 driver structures */
#ifdef MPC_ISRAM0_S
static const struct mpc_sie200_dev_cfg_t MPC_ISRAM0_DEV_CFG_S = {
    .base = MUSCA_MPC_SRAM0_S_BASE};
static struct mpc_sie200_dev_data_t MPC_ISRAM0_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_ISRAM0_DEV_S = {
    &(MPC_ISRAM0_DEV_CFG_S),
    &(MPC_ISRAM0_DEV_DATA_S)};
#endif

#ifdef MPC_ISRAM1_S
static const struct mpc_sie200_dev_cfg_t MPC_ISRAM1_DEV_CFG_S = {
    .base = MUSCA_MPC_SRAM1_S_BASE};
static struct mpc_sie200_dev_data_t MPC_ISRAM1_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_ISRAM1_DEV_S = {
    &(MPC_ISRAM1_DEV_CFG_S),
    &(MPC_ISRAM1_DEV_DATA_S)};
#endif

#ifdef MPC_ISRAM2_S
static const struct mpc_sie200_dev_cfg_t MPC_ISRAM2_DEV_CFG_S = {
    .base = MUSCA_MPC_SRAM2_S_BASE};
static struct mpc_sie200_dev_data_t MPC_ISRAM2_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_ISRAM2_DEV_S = {
    &(MPC_ISRAM2_DEV_CFG_S),
    &(MPC_ISRAM2_DEV_DATA_S)};
#endif

#ifdef MPC_ISRAM3_S
static const struct mpc_sie200_dev_cfg_t MPC_ISRAM3_DEV_CFG_S = {
    .base = MUSCA_MPC_SRAM3_S_BASE};
static struct mpc_sie200_dev_data_t MPC_ISRAM3_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_ISRAM3_DEV_S = {
    &(MPC_ISRAM3_DEV_CFG_S),
    &(MPC_ISRAM3_DEV_DATA_S)};
#endif

#ifdef MPC_CODE_SRAM1_NS
static const struct mpc_sie200_dev_cfg_t MPC_CODE_SRAM1_DEV_CFG_NS = {
    .base = MUSCA_CODE_SRAM_MPC_NS_BASE};
static struct mpc_sie200_dev_data_t MPC_CODE_SRAM1_DEV_DATA_NS = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_CODE_SRAM1_DEV_NS = {
    &(MPC_CODE_SRAM1_DEV_CFG_NS),
    &(MPC_CODE_SRAM1_DEV_DATA_NS)};
#endif

#ifdef MPC_CODE_SRAM1_S
static const struct mpc_sie200_dev_cfg_t MPC_CODE_SRAM1_DEV_CFG_S = {
    .base = MUSCA_CODE_SRAM_MPC_S_BASE};
static struct mpc_sie200_dev_data_t MPC_CODE_SRAM1_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_CODE_SRAM1_DEV_S = {
    &(MPC_CODE_SRAM1_DEV_CFG_S),
    &(MPC_CODE_SRAM1_DEV_DATA_S)};
#endif

#ifdef MPC_QSPI_S
static const struct mpc_sie200_dev_cfg_t MPC_QSPI_DEV_CFG_S = {
    .base = MUSCA_QSPI_MPC_S_BASE};
static struct mpc_sie200_dev_data_t MPC_QSPI_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_QSPI_DEV_S = {
    &(MPC_QSPI_DEV_CFG_S),
    &(MPC_QSPI_DEV_DATA_S)};
#endif

#ifdef MPC_QSPI_NS
static const struct mpc_sie200_dev_cfg_t MPC_QSPI_DEV_CFG_NS = {
    .base = MUSCA_QSPI_MPC_NS_BASE};
static struct mpc_sie200_dev_data_t MPC_QSPI_DEV_DATA_NS = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct mpc_sie200_dev_t MPC_QSPI_DEV_NS = {
    &(MPC_QSPI_DEV_CFG_NS),
    &(MPC_QSPI_DEV_DATA_NS)};
#endif

/* ARM MHU driver structures */
#ifdef ARM_MHU0_S
static const struct arm_mhu_sse_200_dev_cfg_t ARM_MHU0_DEV_CFG_S = {
    .base = MUSCA_MHU0_S_BASE};
struct arm_mhu_sse_200_dev_t ARM_MHU0_DEV_S = {&(ARM_MHU0_DEV_CFG_S)};
#endif
#ifdef ARM_MHU0_NS
static const struct arm_mhu_sse_200_dev_cfg_t ARM_MHU0_DEV_CFG_NS = {
    .base = MUSCA_MHU0_NS_BASE};
struct arm_mhu_sse_200_dev_t ARM_MHU0_DEV_NS = {&(ARM_MHU0_DEV_CFG_NS)};
#endif

#ifdef ARM_MHU1_S
static const struct arm_mhu_sse_200_dev_cfg_t ARM_MHU1_DEV_CFG_S = {
    .base = MUSCA_MHU1_S_BASE};
struct arm_mhu_sse_200_dev_t ARM_MHU1_DEV_S = {&(ARM_MHU1_DEV_CFG_S)};
#endif
#ifdef ARM_MHU1_NS
static const struct arm_mhu_sse_200_dev_cfg_t ARM_MHU1_DEV_CFG_NS = {
    .base = MUSCA_MHU1_NS_BASE};
struct arm_mhu_sse_200_dev_t ARM_MHU1_DEV_NS = {&(ARM_MHU1_DEV_CFG_NS)};
#endif

/* CMSDK Timers driver structures */
#ifdef CMSDK_TIMER0_S
static const struct cmsdk_timer_dev_cfg_t CMSDK_TIMER0_DEV_CFG_S = {
    .base = MUSCA_CMSDK_TIMER0_S_BASE};
static struct cmsdk_timer_dev_data_t CMSDK_TIMER0_DEV_DATA_S = {
    .is_initialized = 0};
struct cmsdk_timer_dev_t CMSDK_TIMER0_DEV_S = {&(CMSDK_TIMER0_DEV_CFG_S),
                                               &(CMSDK_TIMER0_DEV_DATA_S)};
#endif
#ifdef CMSDK_TIMER0_NS
static const struct cmsdk_timer_dev_cfg_t CMSDK_TIMER0_DEV_CFG_NS = {
    .base = MUSCA_CMSDK_TIMER0_NS_BASE};
static struct cmsdk_timer_dev_data_t CMSDK_TIMER0_DEV_DATA_NS = {
    .is_initialized = 0};
struct cmsdk_timer_dev_t CMSDK_TIMER0_DEV_NS = {&(CMSDK_TIMER0_DEV_CFG_NS),
                                                &(CMSDK_TIMER0_DEV_DATA_NS)};
#endif

#ifdef CMSDK_TIMER1_S
static const struct cmsdk_timer_dev_cfg_t CMSDK_TIMER1_DEV_CFG_S = {
    .base = MUSCA_CMSDK_TIMER1_S_BASE};
static struct cmsdk_timer_dev_data_t CMSDK_TIMER1_DEV_DATA_S = {
    .is_initialized = 0};
struct cmsdk_timer_dev_t CMSDK_TIMER1_DEV_S = {&(CMSDK_TIMER1_DEV_CFG_S),
                                               &(CMSDK_TIMER1_DEV_DATA_S)};
#endif
#ifdef CMSDK_TIMER1_NS
static const struct cmsdk_timer_dev_cfg_t CMSDK_TIMER1_DEV_CFG_NS = {
    .base = MUSCA_CMSDK_TIMER1_NS_BASE};
static struct cmsdk_timer_dev_data_t CMSDK_TIMER1_DEV_DATA_NS = {
    .is_initialized = 0};
struct cmsdk_timer_dev_t CMSDK_TIMER1_DEV_NS = {&(CMSDK_TIMER1_DEV_CFG_NS),
                                                &(CMSDK_TIMER1_DEV_DATA_NS)};
#endif

/* CMSDK Dualtimer driver structures */
#ifdef CMSDK_DUALTIMER_S
static const struct apb_dualtimer_dev_cfg_t CMSDK_DUALTIMER_DEV_CFG_S = {
    .base = MUSCA_CMSDK_DUALTIMER_S_BASE};
static struct apb_dualtimer_dev_data_t CMSDK_DUALTIMER_DEV_DATA_S = {
    .timer1_reload = 0,
    .timer2_reload = 0,
    .state = 0};
struct apb_dualtimer_dev_t CMSDK_DUALTIMER_DEV_S = {
    &(CMSDK_DUALTIMER_DEV_CFG_S),
    &(CMSDK_DUALTIMER_DEV_DATA_S)};
#endif

#ifdef CMSDK_DUALTIMER_NS
static const struct apb_dualtimer_dev_cfg_t CMSDK_DUALTIMER_DEV_CFG_NS = {
    .base = MUSCA_CMSDK_DUALTIMER_NS_BASE};
static struct apb_dualtimer_dev_data_t CMSDK_DUALTIMER_DEV_DATA_NS = {
    .timer1_reload = 0,
    .timer2_reload = 0,
    .state = 0};
struct apb_dualtimer_dev_t CMSDK_DUALTIMER_DEV_NS = {
    &(CMSDK_DUALTIMER_DEV_CFG_NS),
    &(CMSDK_DUALTIMER_DEV_DATA_NS)};
#endif

#ifdef UART0_PL011_S
static const struct uart_pl011_dev_cfg_t UART0_DEV_CFG_S = {
    .base = MUSCA_UART0_S_BASE,
    .def_baudrate = 115200,
    .def_wlen = UART_PL011_WLEN_8,
    .def_parity = UART_PL011_PARITY_DISABLED,
    .def_stopbit = UART_PL011_STOPBIT_1};
static struct uart_pl011_dev_data_t UART0_DEV_DATA_S = {
    .state = 0,
    .uart_clk = 0,
    .baudrate = 0};
struct uart_pl011_dev_t UART0_DEV_S = {&(UART0_DEV_CFG_S),
                                               &(UART0_DEV_DATA_S)};
#endif

#ifdef UART0_PL011_NS
static const struct uart_pl011_dev_cfg_t UART0_DEV_CFG_NS = {
    .base = MUSCA_UART0_NS_BASE,
    .def_baudrate = 115200,
    .def_wlen = UART_PL011_WLEN_8,
    .def_parity = UART_PL011_PARITY_DISABLED,
    .def_stopbit = UART_PL011_STOPBIT_1};
static struct uart_pl011_dev_data_t UART0_DEV_DATA_NS = {
    .state = 0,
    .uart_clk = 0,
    .baudrate = 0};
struct uart_pl011_dev_t UART0_DEV_NS = {&(UART0_DEV_CFG_NS),
                                                &(UART0_DEV_DATA_NS)};
#endif

#ifdef UART1_PL011_S
static const struct uart_pl011_dev_cfg_t UART1_DEV_CFG_S = {
    .base = MUSCA_UART1_S_BASE,
    .def_baudrate = 115200,
    .def_wlen = UART_PL011_WLEN_8,
    .def_parity = UART_PL011_PARITY_DISABLED,
    .def_stopbit = UART_PL011_STOPBIT_1};
static struct uart_pl011_dev_data_t UART1_DEV_DATA_S = {
    .state = 0,
    .uart_clk = 0,
    .baudrate = 0};
struct uart_pl011_dev_t UART1_DEV_S = {&(UART1_DEV_CFG_S),
                                               &(UART1_DEV_DATA_S)};
#endif

#ifdef UART1_PL011_NS
static const struct uart_pl011_dev_cfg_t UART1_DEV_CFG_NS = {
    .base = MUSCA_UART1_NS_BASE,
    .def_baudrate = 115200,
    .def_wlen = UART_PL011_WLEN_8,
    .def_parity = UART_PL011_PARITY_DISABLED,
    .def_stopbit = UART_PL011_STOPBIT_1};
static struct uart_pl011_dev_data_t UART1_DEV_DATA_NS = {
    .state = 0,
    .uart_clk = 0,
    .baudrate = 0};
struct uart_pl011_dev_t UART1_DEV_NS = {&(UART1_DEV_CFG_NS),
                                                &(UART1_DEV_DATA_NS)};
#endif
