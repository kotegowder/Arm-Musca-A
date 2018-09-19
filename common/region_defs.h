/*
 * Copyright (c) 2016-2017 ARM Limited
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

#ifndef REGION_DEFS_H
#define REGION_DEFS_H

#include "region_limits.h"

/* Alias definitions for secure and non-secure areas */
#define S_ROM_ALIAS(x)  ((S_ROM_ALIAS_BASE)+(x))
#define NS_ROM_ALIAS(x) ((NS_ROM_ALIAS_BASE)+(x))

#define S_RAM_ALIAS(x)  ((S_RAM_ALIAS_BASE)+(x))
#define NS_RAM_ALIAS(x) ((NS_RAM_ALIAS_BASE)+(x))

/* *********************************************************
 * WARNING: this file is parsed both by the C/C++ compiler
 * and the linker:s. As a result the syntax must be valid not only
 * for C/C++ but for the linker scripts too.
 * Beware of the following limitations:
 *   - LD (GCC linker) requires white space around operators.
 ***********************************************************/

/* Secure regions */
#define S_CODE_START     ( S_ROM_ALIAS(0x0) )
#define S_CODE_SIZE      ( TOTAL_ROM_SIZE )
#define S_CODE_LIMIT     ( S_CODE_START + S_CODE_SIZE )

#define S_DATA_START     ( S_RAM_ALIAS(0x0) )
#define S_DATA_SIZE      ( TOTAL_RAM_SIZE / 2 )
#define S_DATA_LIMIT     ( S_DATA_START + S_DATA_SIZE )

/* Non-secure regions */
#define NS_CODE_START    ( NS_ROM_ALIAS(TOTAL_ROM_SIZE / 2) )
#define NS_CODE_SIZE     ( TOTAL_ROM_SIZE / 2 )
#define NS_CODE_LIMIT    ( NS_CODE_START + NS_CODE_SIZE )

#define NS_DATA_START    ( NS_RAM_ALIAS(TOTAL_RAM_SIZE / 2) )
#define NS_DATA_SIZE     ( TOTAL_RAM_SIZE / 2 )
#define NS_DATA_LIMIT    ( NS_DATA_START + NS_DATA_SIZE )

#define VENEER_SIZE      (S_CODE_SIZE-ImageLength(ER_CODE) \
                          -(AlignExpr(ImageLimit(ER_CODE), 32) \
                          -ImageLimit(ER_CODE)))

/*** Dual-core definitions ***/
#ifdef DUAL_CORE

#define TOTAL_SECURE_ROM_SIZE (TOTAL_ROM_SIZE / 2)
#define TOTAL_SECURE_RAM_SIZE (TOTAL_RAM_SIZE / 2)

/* Use SRAM1 memory to store Code data */
#define CORE0_ROM_ALIAS_BASE S_ROM_ALIAS_BASE

/* Use SRAM2 memory to store RW data */
#define CORE0_RAM_ALIAS_BASE S_RAM_ALIAS_BASE

/* Alias definitions for CORE 0 and CORE 1 CPUs*/
#define CORE0_ROM_ALIAS(x) ((CORE0_ROM_ALIAS_BASE)+(x))

#define CORE0_RAM_ALIAS(x) ((CORE0_RAM_ALIAS_BASE)+(x))

/* CORE 0 regions */
#define CORE0_CODE_START   ( CORE0_ROM_ALIAS(0x0) )
#define CORE0_CODE_SIZE    ( TOTAL_SECURE_ROM_SIZE / 2 )
#define CORE0_CODE_LIMIT   ( CORE0_CODE_START + CORE0_CODE_SIZE )

#define CORE0_DATA_START   ( CORE0_RAM_ALIAS(0x0) )
#define CORE0_DATA_SIZE    ( TOTAL_SECURE_RAM_SIZE / 2 )
#define CORE0_DATA_LIMIT   ( CORE0_DATA_START + CORE0_DATA_SIZE )

/* CORE 1 regions */
#define CORE1_CODE_START   ( CORE0_CODE_LIMIT )
#define CORE1_CODE_SIZE    ( TOTAL_SECURE_ROM_SIZE / 2 )
#define CORE1_CODE_LIMIT   ( CORE1_CODE_START + CORE1_CODE_SIZE )

#define CORE1_DATA_START   ( CORE0_DATA_LIMIT )
#define CORE1_DATA_SIZE    ( TOTAL_SECURE_RAM_SIZE / 2 )
#define CORE1_DATA_LIMIT   ( CORE1_DATA_START + CORE1_DATA_SIZE )

/* Set target dependent memory regions */
#undef S_CODE_START
#undef S_CODE_SIZE
#undef S_DATA_START
#undef S_DATA_SIZE

#if defined CORE0
#define S_CODE_START    CORE0_CODE_START
#define S_CODE_SIZE     CORE0_CODE_SIZE
#define S_DATA_START    CORE0_DATA_START
#define S_DATA_SIZE     CORE0_DATA_SIZE
#elif defined CORE1
#define S_CODE_START    CORE1_CODE_START
#define S_CODE_SIZE     CORE1_CODE_SIZE
#define S_DATA_START    CORE1_DATA_START
#define S_DATA_SIZE     CORE1_DATA_SIZE
#endif

#endif /* DUAL_CORE */
#endif /*REGION_DEFS_H*/

