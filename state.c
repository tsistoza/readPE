
#include "state.h"

enum msdos find_StateMSDOS(int addr,enum msdos state,int offset){
    enum msdos temp = state;
    switch(temp){
        case MAGIC     : if(offset+2 == addr)
                              temp = BYTES;
                         break;
        case BYTES     : if(offset+4 == addr)
                                temp = PAGES;
                           break;
        case PAGES     : if(offset+6 == addr)
                                temp = RELOC;
                           break;
        case RELOC     : if(offset+8 == addr)
                                temp = HEAD;
                           break;
        case HEAD      : if(offset+10 == addr)
                                temp = MIN_XTRA;
                           break;
        case MIN_XTRA  : if(offset+12 == addr)
                                temp = MAX_XTRA;
                           break;
        case MAX_XTRA  : if(offset+14 == addr)
                                temp = INIT_SS;
                           break;
        case INIT_SS   : if(offset+16 == addr)
                                temp = INIT_SP;
                           break;
        case INIT_SP   : if(offset+18 == addr)
                                temp = X1;
                           break;
        case X1        : if(offset+20 == addr)
                                temp = INIT_IP;
                           break;
        case INIT_IP   : if(offset+22 == addr)
                                temp = INIT_CS;
                           break;
        case INIT_CS   : if(offset+24 == addr)
                                temp = ADDR_RELOC;
                           break;
        case ADDR_RELOC: if(offset+26 == addr)
                                temp = OVERLAY;
                           break;
        case OVERLAY   : if(offset+28 == addr)
                                temp = X2;
                           break;
        case X2        : if(offset+36 == addr)
                                temp = OEM_ID;
                           break;
        case OEM_ID    : if(offset+38 == addr)
                                temp = OEM_info;
                           break;
        case OEM_info  : if(offset+40 == addr)
                                temp = X3;
                           break;
        case X3        : if(offset+60 == addr)
                                temp = PE_HEAD;
                           break;
        case PE_HEAD   : if(offset+62 == addr)
                                temp = XTRA;
                           break;
        case XTRA      :   break;
        default          : printf("UNKNOWN SECTION\n");
                           break;
    }
    return temp;
}


enum coff find_StateCOFF(int addr,enum coff state,int offset){
    enum coff temp=state;
    switch(temp){
          case MACH    : if(offset+6 == addr)
                              temp = SECTION;
                         break;
          case SECTION : if(offset+8 == addr)
                              temp = DATE;
                         break;
          case DATE    : if(offset+12 == addr)
                              temp = SYM_OFF;
                         break;
          case SYM_OFF : if(offset+16 == addr)
                              temp = numSYM;
                         break;
          case numSYM  : if(offset+20 == addr)
                              temp = sizeHEAD;
                         break;
          case sizeHEAD: if(offset+22 == addr)
                              temp = CHARC;
                         break;
          case CHARC   : if(offset+24 == addr)
                              temp = XTR;
                         break;
          case XTR     : break;
          default      : break;
    }
    return temp;
}

//@TODO IMPLEMENT STATE MACHINE FOR OPT
enum opt find_StateOPT(int addr,enum opt state,int offset,int value){
     enum opt temp = state;
     switch(temp){
        case MAG_NUM      : if(offset+2 == addr)   temp=MAJ_LINK;
		                  break;
        case MAJ_LINK     : if(offset+3 == addr)   temp=MIN_LINK;
		                  break;
        case MIN_LINK     : if(offset+4 == addr)   temp=TEXT_SIZE;
		                  break;
        case TEXT_SIZE    : if(offset+8 == addr)   temp=DATA_SIZE;
			             break;
        case DATA_SIZE    : if(offset+12 == addr)  temp=BSS_SIZE;
			             break;
        case BSS_SIZE     : if(offset+16 == addr)  temp=ENTRY_PT;
		                  break;
        case ENTRY_PT     : if(offset+20 == addr)  temp=TEXT_ADDR;
		                  break;
        case TEXT_ADDR    : if(offset+24 == addr)  temp=DATA_ADDR;
		                  break;
        case DATA_ADDR    : if(offset+28 == addr)  temp=IMG_BASE;
			             break;
        
        //FOR PE32+ Section
        
        case IMG_BASE     : if(value == 0x10b && offset+32==addr) temp=ALIGN_SEC;
                            else if(value == 0x20b && offset+32==addr) temp=ALIGN_SEC;
			             break;

        case ALIGN_SEC    : if(value == 0x10b && offset+36==addr) temp=ALIGN_FILE;
                            else if(value == 0x20b && offset+36==addr)  temp=ALIGN_FILE;
			             break;

        case ALIGN_FILE   : if(value == 0x10b && offset+40==addr)  temp=MAJ_OS;
                            else if(value == 0x20b && offset+40==addr)  temp=MAJ_OS;
			             break;

        case MAJ_OS       : if(value == 0x10b && offset+42==addr)  temp=MIN_OS;
                            else if(value == 0x20b && offset+42==addr)  temp=MIN_OS;
			             break;

        case MIN_OS       : if(value == 0x10b && offset+44==addr)  temp=MAJ_IMG;
                            else if(value == 0x20b && offset+44==addr)  temp=MAJ_IMG;
			             break;

        case MAJ_IMG      : if(value == 0x10b && offset+46==addr)  temp=MIN_IMG;
                            else if(value == 0x20b && offset+46==addr)  temp=MIN_IMG;
			             break;

        case MIN_IMG      : if(value == 0x10b && offset+48==addr)  temp=MAJ_SUB;
                            else if(value == 0x20b && offset+48==addr)  temp=MAJ_SUB;
		    	             break;

        case MAJ_SUB      : if(value == 0x10b && offset+50==addr)  temp=MIN_SUB;
                            else if(value == 0x20b && offset+50==addr)  temp=MIN_SUB;
			             break;

        case MIN_SUB      : if(value == 0x10b && offset+52==addr)  temp=Y1;
                            else if(value == 0x20b && offset+52==addr)  temp=Y1;
			             break;

        case Y1           : if(value == 0x10b && offset+56==addr)  temp=SIZE_IMG;
                            else if(value == 0x20b && offset+56==addr)  temp=SIZE_IMG;
			             break;

        case SIZE_IMG     : if(value == 0x10b && offset+60==addr)  temp=SIZE_HEAD;
                            else if(value == 0x20b && offset+60==addr)  temp=SIZE_HEAD;
          	             break;

        case SIZE_HEAD    : if(value == 0x10b && offset+64==addr)  temp=CKSUM;
                            else if(value == 0x20b && offset+64==addr)  temp=CKSUM;
			             break;

        case CKSUM        : if(value == 0x10b && offset+68==addr)  temp=SUBSYS;
                            else if(value == 0x20b && offset+68==addr)  temp=SUBSYS;
			             break;

        case SUBSYS       : if(value == 0x10b && offset+70==addr)  temp=DLL_CHAR;
                            else if(value == 0x20b && offset+70==addr)  temp=DLL_CHAR;
			             break;

        case DLL_CHAR     : if(value == 0x10b && offset+72==addr)  temp=SIZE_stackRES;
                            else if(value == 0x20b && offset+72==addr)  temp=SIZE_stackRES;
			             break;

        case SIZE_stackRES: if(value == 0x10b && offset+76==addr)  temp=SIZE_stackCOM;
                            else if(value == 0x20b && offset+80==addr)  temp=SIZE_stackCOM;
     			        break;

        case SIZE_stackCOM: if(value == 0x10b && offset+80==addr)  temp=SIZE_heapRES;
                            else if(value == 0x20b && offset+88==addr)  temp=SIZE_heapRES;
                            break;

        case SIZE_heapRES : if(value == 0x10b && offset+84==addr)  temp=SIZE_heapCOM;
                            else if(value == 0x20b && offset+96==addr)  temp=SIZE_heapCOM;
                            break;

        case SIZE_heapCOM : if(value == 0x10b && offset+88==addr)  temp=Y2;
                            else if(value == 0x20b && offset+104==addr)  temp=Y2;
			             break;

        case Y2           : if(value == 0x10b && offset+92==addr)  temp=Y3;
                            else if(value == 0x20b && offset+108==addr)  temp=Y3;
			             break;

        case Y3           : if(value == 0x10b && offset+96==addr)  temp=END_OPT;
                            else if(value == 0x20b && offset+112==addr)  temp=END_OPT;
     			        break;

        case END_OPT      : break;
        default           : printf("UNKNOWN SECTION\n");
                            break;
     }
     return temp;
}

enum sect find_StateSECT(int addr,enum sect state,int offset){
     enum sect temp = state;
     switch(temp){
          case sectHeader   : if(offset+8 == addr) temp = virtSize;
                              break;
          case virtSize   : if(offset+12 == addr) temp = virtAddr;
                            break;
          case virtAddr   : if(offset+16 == addr) temp = sizeRawData;
                            break;
          case sizeRawData: if(offset+20 == addr) temp = ptrRawData;
                            break;
          case ptrRawData : if(offset+24 == addr) temp = ptrReloc;
                            break;
          case ptrReloc   : if(offset+28 == addr) temp = ptrLine;
                            break;
          case ptrLine    : if(offset+32 == addr) temp = numReloc;
                            break;
          case numReloc   : if(offset+34 == addr) temp = numLineNum;
                            break;
          case numLineNum : if(offset+36 == addr) temp = sectChars;
                            break;
          case sectChars  : if(offset+40 == addr) temp = endSect;
                            break;
          default         :
                            break;
     }
     return temp;
}

