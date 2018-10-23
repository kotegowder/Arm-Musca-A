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

#ifndef __S_NS_SHARED_H__
#define __S_NS_SHARED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
 * Linker generated symbols for start and limit address of the section used to
 * store the veneers for functions marked as cmse_nonsecure_entry.
 * We declare them as array so that the "value" of the variable is the value of
 * the symbol itself instead of the value found at the location pointed to by
 * the symbol's value.
 * These addresses should be aligned on 32 bytes boundary
 * so that we do not accidentaly set as Non-Secure Callable the beginning
 * of the next region.

 * Note: These symbols are created by armlink upon reference. If using GNU ld,
 * you will need to create these symbols manually in the linker script and
 * change the macro definition accordingly.
 */
extern const uint32_t Image$$ER_CODE_CMSE_VENEER$$Base;
extern const uint32_t Image$$ER_CODE_CMSE_VENEER$$Limit;
#define CMSE_VENEER_REGION_BASE  ((uint32_t)&Image$$ER_CODE_CMSE_VENEER$$Base)
#define CMSE_VENEER_REGION_LIMIT ((uint32_t)&Image$$ER_CODE_CMSE_VENEER$$Limit)

/*
 * This function pointer is meant to only hold non secure function pointers.
 * It will be turned into a non-secure one (LSB cleared) before being called
 * whatever happens anyway (unless cast to another function pointer type).
 * Registers will be cleared before branching so that no information leaks
 * from secure to non-secure world.

 * Related documentation:
 * https://developer.arm.com/docs/100070/latest/scatter-loading-features/placement-of-cmse-veneer-sections-for-a-secure-image
 */
typedef void __attribute__((cmse_nonsecure_call)) (*nsfptr_t) (void);

/*
 * Those functions are an entry point for the non-secure world. That means
 * that the non-secure world can call this function through the veneer placed
 * in a non-secure callable area.
 * If the secure world tries to take the address of this function,
 * it may get the address of the veneer or the adress of the function
 * itself, depending on linker implementation.
 * If the non-secure world tries to take the address of this function,
 * it will always get the address of the veneer (as defined in the
 * s_veneers.o generated with --import_cmse_lib_out on armclang).
 */

/**
 * \brief Set secure LED port by the given value.
 *        The LED port is enabled to be written only by
 *        predefined frequency.
 *
 * \param[in] led_port_value Value of LED port request to be written.
 *
 * \return Result of the request, zero if succeeeded
 */
extern unsigned int set_secure_led_port(unsigned int led_port_value)
       __attribute__((cmse_nonsecure_entry, noinline));

#ifdef __cplusplus
}
#endif
#endif /* __S_NS_SHARED_H__ */
