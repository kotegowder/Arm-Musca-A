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

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "uart_pl011_drv.h"

/**
 * \brief Initializes default UART device
 */
void serial_init(void);

/**
 * \brief Prints a string through the default UART device
 */
void serial_print(char *str);

//#define printf(fmt,...) {char buf[64]={0}; sprintf(buf, fmt,__VA_ARGS__); serial_print(buf);}
int printf(const char * format, ...); 

#endif /* __SERIAL_H__ */
