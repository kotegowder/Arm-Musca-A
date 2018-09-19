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

#include "serial.h"
#include "get_serial.h"
#include "system_musca.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void serial_init(void)
{
    struct uart_pl011_dev_t* uart_dev = get_stdio_uart_dev();

    if(uart_dev != NULL) {
        uart_pl011_init(uart_dev, SystemCoreClock);
        uart_pl011_enable(uart_dev);
    }
}

void serial_print(char * str)
{
    struct uart_pl011_dev_t* uart_dev = get_stdio_uart_dev();

    if(uart_dev != NULL) {
        size_t len = strlen(str);
        while(len--) {
            while(!uart_pl011_is_writable(uart_dev));
            uart_pl011_write(uart_dev, *str);
            str++;
        }
    }
}

int printf(const char * format, ...)
{
	va_list arg;
	char buffer[BUFSIZ]={0};
	int len = 0;
	va_start(arg, format);
	len = vsprintf(buffer, format, arg);
	va_end(arg);
	serial_print(buffer);
	return len; 
}