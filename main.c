#include <stdio.h>
#include <stdlib.h>

#include "cmsis.h"
#include "serial.h"

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
__asm("  .global __ARM_use_no_argv\n");
#endif

int main (void)
{
    serial_init();

    printf("\n\rStarting Arm Musca-A : %s", __DATE__);
	
    while(1);
}
