
#include "SectionSize.h"

int sizeSectionMS(enum msdos state){
    int temp=0;
    switch(state){
        case X2        : return (temp = 8);
                         break;
        case X3        : return (temp = 20);
                         break;
        default        : return (temp = 2);
                         break;
    }
}


int sizeSectionCOFF(enum coff state1){
    int temp=0;
    switch(state1){
        case DATE    : temp=4;
                       break;
        case SYM_OFF : temp=4;
                       break;
        case numSYM  : temp=4;
                       break;
        default      : return (temp = 2);
    }
    return temp;
}

int sizeSectionOPT(enum opt state1,int value){
    int temp=0;
    switch(state1){
        case MAG_NUM       : temp = 2;
                             break;
        case MAJ_LINK      : temp = 1;
                             break;
        case MIN_LINK      : temp = 1;
                             break;
        case IMG_BASE      : if(value == 0x10b)
                                temp = 4;
                             else
                                temp = 8;
                             break;
        case MAJ_OS        : temp = 2;
                             break;
        case MIN_OS        : temp = 2;
                             break;
        case MAJ_IMG       : temp = 2;
                             break;
        case MIN_IMG       : temp = 2;
                             break;
        case MAJ_SUB       : temp = 2;
                             break;
        case SUBSYS        : temp = 2;
                             break;
        case DLL_CHAR      : temp = 2;
                             break;
        case SIZE_stackRES : if(value == 0x10b)
                                temp = 4;
                             else
                                temp = 8;
                             break; 
        case SIZE_stackCOM : if(value == 0x10b)
                                temp = 4;
                             else
                                temp = 8;
                             break;
        case SIZE_heapRES  : if(value == 0x10b)
                                temp = 4;
                             else
                                temp = 8;
                             break;
        case SIZE_heapCOM  : if(value == 0x10b)
                                temp = 4;
                             else
                                temp = 8;
                             break;
        default            : temp = 4;
                             break;
    }
    return temp;
}

int sizeSectionHeader(enum sect state){
   int temp = 0;
   switch(state){
      case sectHeader : temp = 8;
                        break;
      case numReloc   : temp = 2;
                        break;
      case numLineNum : temp = 2;
                        break;
      default         : temp = 4;
                        break;
   }
   return temp;
}
