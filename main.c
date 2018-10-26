#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmsis.h"
#include "region_defs.h"
#include "serial.h"
#include "s_secure_config.h"
#include "s_ns_shared.h"

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
__asm("  .global __ARM_use_no_argv\n");
#endif

#define outpw(port,value)   (*((volatile unsigned int *)(port))=(value))
#define inpw(port)          ((*((volatile unsigned int *)(port))))

typedef void (*FUNC_PTR)(void);

extern uint32_t LoaderImage_S_Text_Base, LoaderImage_S_Text_Limit;
extern uint32_t LoaderImage_S_Data_Base, LoaderImage_S_Data_Limit;
extern uint32_t LoaderImage_NSC_Entry_Base, LoaderImage_NSC_Entry_Limit;
extern uint32_t LoaderImage_NS_Text_Base, LoaderImage_NS_Text_Limit;
extern uint32_t LoaderImage_NS_Data_Base, LoaderImage_NS_Data_Limit;
extern uint32_t LoaderImage_Test_Base, LoaderImage_Test_Limit;

static int LoadImage(uint32_t u32ImageBase, uint32_t u32ImageLimit, uint32_t u32FlashAddr, uint32_t u32MaxSize)
{
    uint32_t   i, j, u32Data, u32ImageSize, *pu32Loader;

    u32ImageSize = u32MaxSize;

    //printf("Program image to SRAM address 0x%x...", u32FlashAddr);

    pu32Loader = (uint32_t *)u32ImageBase;
    for(i = 0; i < u32ImageSize; i += 4)
    {
        outpw(u32FlashAddr+i, pu32Loader[(i>>2)]);
    }

    printf("\n\rVerify ... ");

    /* Verify loader */
    for(i = 0; i < u32ImageSize; i += 4)
    {
        u32Data = inpw(u32FlashAddr+i);

        if(u32Data != pu32Loader[(i>>2)])
        {
            printf("\n\rdata mismatch on 0x%x, [0x%x], [0x%x]\n", u32FlashAddr+i, u32Data, pu32Loader[i/4]);
            return -1;
        }
    }
    printf("\n\rOK.\n");
    return 0;
}

void tt_response(int tt_adr)
{
    unsigned int tt_resp;
	__ASM("tt %0, %1" : "=r" (tt_resp) : "r" (tt_adr));
	if (tt_resp & (1UL << 22)) {
		  printf("\n\rResp : %X, Address %X is secure", tt_resp, tt_adr);
	} else {
		  printf("\n\rResp : %X, Address %X is Non-secure", tt_resp, tt_adr);
	}
}

int main (void)
{
    serial_init();

    printf("\n\rStarting Arm Musca-A : %s", __DATE__);

		/* Configure resources between secure and non-secure worlds */
    SAU_and_IDAU_config();
    MPC_config();

    printf("\n\n");
    printf("\n\r+----------------------------------------------+");
    printf("\n\r|                     TBSA                     |");
    printf("\n\r+----------------------------------------------+");
    printf("\n\r Main App S_Text    start[0x%08X] end[0x%08X]", (uint32_t)&LoaderImage_S_Text_Base, (uint32_t)&LoaderImage_S_Text_Limit);
    printf("\n\r Main App S_Data    start[0x%08X] end[0x%08X]", (uint32_t)&LoaderImage_S_Data_Base, (uint32_t)&LoaderImage_S_Data_Limit);
    printf("\n\r Main App NSC_Entry start[0x%08X] end[0x%08X]", (uint32_t)&LoaderImage_NSC_Entry_Base, (uint32_t)&LoaderImage_NSC_Entry_Limit);
    printf("\n\r Main App NS_Text   start[0x%08X] end[0x%08X]", (uint32_t)&LoaderImage_NS_Text_Base, (uint32_t)&LoaderImage_NS_Text_Limit);
    printf("\n\r Main App NS_Data   start[0x%08X] end[0x%08X]", (uint32_t)&LoaderImage_NS_Data_Base, (uint32_t)&LoaderImage_NS_Data_Limit);
    printf("\n\r Test Code          start[0x%08X] end[0x%08X]\n\n", (uint32_t)&LoaderImage_Test_Base, (uint32_t)&LoaderImage_Test_Limit);

#if 0
		tt_response(0x30000000UL);
		tt_response(0x20010000UL);
		tt_response(0x20014000UL);
		tt_response(0x20014800UL);
		tt_response(0x10000000UL);
		tt_response(0x20018000UL);
		printf("\n");
#endif
		uint32_t dst_adr  = 0x30007000UL;
		uint32_t dst_size = 0x8000; /* 32KB */
		printf("\n\rMain App S_Text to     addr[%X] size[%X] ... ", dst_adr, dst_size);
    LoadImage((uint32_t)&LoaderImage_S_Text_Base, (uint32_t)&LoaderImage_S_Text_Limit, 0x30007000, 0x8000);

		dst_adr  = 0x3000F000UL;
		dst_size = 0xC00; /* 3KB */
    printf("\n\rMain App S_Data to     addr[%X] size[%X] ... ", dst_adr, dst_size);
    LoadImage((uint32_t)&LoaderImage_S_Data_Base, (uint32_t)&LoaderImage_S_Data_Limit, dst_adr, dst_size);

		dst_adr  = 0x10000000UL;
		dst_size = 0x2000; /* 8KB */
		printf("\n\rMain App NSCS_Entry to addr[%X] size[%X] ... ", dst_adr, dst_size);
		LoadImage((uint32_t)&LoaderImage_NSC_Entry_Base, (uint32_t)&LoaderImage_NSC_Entry_Base, dst_adr, dst_size);

		dst_adr  = 0x20014000UL;
		dst_size = 0x1800; /* 6KB */
		printf("\n\rMain App NS_Data to    addr[%X] size[%X] ... ", dst_adr, dst_size);
    LoadImage((uint32_t)&LoaderImage_NS_Data_Base, (uint32_t)&LoaderImage_NS_Data_Limit, dst_adr, dst_size);

		dst_adr  = 0x20015800UL;
		dst_size = 0x800; /* 2KB */
    printf("\n\rMain App NS_Text to    addr[%X] size[%X] ... ", dst_adr, dst_size);
    LoadImage((uint32_t)&LoaderImage_NS_Text_Base, (uint32_t)&LoaderImage_NS_Text_Limit, dst_adr, dst_size);

    if (inpw(0x50021000UL + 0x100) & 0x1) {
				printf("\n\rPower On reset\n");
				/* NVRAM Initialization */
			  memset((void *)0x3000FC10, 0xFF, 128);
		}

		if ((inpw(0x50021000UL + 0x100) & 0x10UL) || (inpw(0x50021000UL + 0x100) & 0x20UL)) {
		    outpw((0x50021000UL + 0x100), (inpw(0x50021000UL + 0x100) & 0xFFFFFFFEUL));
		}

    /* Run to MAIN_APP_S */
    FUNC_PTR fp;

    fp = ((FUNC_PTR)(0x30007000+1));

		fp();
	
		printf("\n\rEntering while()");
    while(1);
}
