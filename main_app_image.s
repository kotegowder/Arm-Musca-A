;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2013 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  LoaderImage_S_Text_Base
    EXPORT  LoaderImage_S_Text_Limit
        
    EXPORT  LoaderImage_S_Data_Base
    EXPORT  LoaderImage_S_Data_Limit  
 
    EXPORT  LoaderImage_NSC_Entry_Base
    EXPORT  LoaderImage_NSC_Entry_Limit  
        
    EXPORT  LoaderImage_NS_Text_Base
    EXPORT  LoaderImage_NS_Text_Limit
        
    EXPORT  LoaderImage_NS_Data_Base
    EXPORT  LoaderImage_NS_Data_Limit          
    
    ALIGN   4
        
LoaderImage_S_Text_Base
    INCBIN TBSA_out\.text
LoaderImage_S_Text_Limit

LoaderImage_S_Data_Base
    INCBIN TBSA_out\.data
LoaderImage_S_Data_Limit

LoaderImage_NSC_Entry_Base
    INCBIN TBSA_out\.tbsa_nsc_entry_points
LoaderImage_NSC_Entry_Limit

LoaderImage_NS_Text_Base
    INCBIN TBSA_out\.tbsa_ns_text
LoaderImage_NS_Text_Limit

LoaderImage_NS_Data_Base
    INCBIN TBSA_out\.tbsa_ns_data
LoaderImage_NS_Data_Limit

	END