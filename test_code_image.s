;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2013 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  LoaderImage_Test_Base
    EXPORT  LoaderImage_Test_Limit
    
    ALIGN   4
        
LoaderImage_Test_Base
   INCBIN ./TBSA_out/tbsa_test_combined.bin
LoaderImage_Test_Limit

    END