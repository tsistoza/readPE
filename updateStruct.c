
#include "updateStruct.h"

//Strings for Print
struct MN{
    const char* MSDOS_MN;
    const char* OPT_MN1;
    const char* OPT_MN2;
} MAG = {.MSDOS_MN = "(MZ)", .OPT_MN1 = "(PE32)", .OPT_MN2 ="(PE32+)"};

const char* recSUB = "IMAGE_SUBSYSTEM_WINDOWS_CUI";

void updateMS(struct MSDOS *x, enum msdos state, int update){

    switch(state){
        case MAGIC     : if(update == 0x5a4d)
                            x->MAGIC_NUM = update;
                         else{
                            printf("readpe: UNKNOWN FILETYPE\n");
                            exit(0);
                         }
                         break;
        case BYTES     : x->BYTES_LAST_PAGE = update;
                         break;
        case PAGES     : x->PAGES_IN_FILE = update;
                         break;
        case RELOC     : x->RELOCATIONS = update;
                         break;
        case HEAD      : x->SIZE_OF_HEADER_IN_PARAGRAPHS = update;
                         break;
        case MIN_XTRA  : x->MIN_XTRA_PARA = update;
                         break;
        case MAX_XTRA  : x->MAX_XTRA_PARA = (unsigned short) update;
                         break;
        case INIT_SS   : x->INITIAL_SS_VALUE = update;
                         break;
        case INIT_SP   : x->SP_VALUE = update;
                         break;
        case INIT_IP   : x->IP_VALUE = update;
                         break;
        case INIT_CS   : x->INIT_CS_VALUE = update;
                         break;
        case ADDR_RELOC: x->ADDR_RELOC = update;
                         break;
        case OVERLAY   : x->OVERLAY_NUM = update;
                         break;
        case OEM_ID    : x->OEM_ID = update;
                         break;
        case OEM_info  : x->OEM_INFO = update;
                         break;
        case PE_HEAD   : x->PE_HEADER_OFFSET = update;
                         break;
        default        : break;
    }

    #ifdef DEBUG
    printf("UPDATED Struct:\n");
    printf("Updating DATA #%d\n",state);
    ms_print(temp);
    printf("\n");
    #endif
}

void ms_print(struct MSDOS *x){
    printf("MSDOS Header:\n");
    printf("    Magic Number:                    0x%04" PRIx16 " %s\n",      x->MAGIC_NUM,MAG.MSDOS_MN); //@TODO STRING MN
    printf("    Bytes in last Page:              %" PRIuLEAST16 "\n",     x->BYTES_LAST_PAGE);
    printf("    Pages in File:                   %" PRIuLEAST16 "\n",     x->PAGES_IN_FILE);
    printf("    Relocations:                     %" PRIuLEAST16 "\n",     x->RELOCATIONS);
    printf("    Size of header in paragraphs:    %" PRIuLEAST16 "\n",     x->SIZE_OF_HEADER_IN_PARAGRAPHS);
    printf("    Minimum extra paragraphs:        %" PRIuLEAST16 "\n",     x->MIN_XTRA_PARA);
    printf("    Maximum extra paragraphs:        %" PRIuLEAST16 "\n",     x->MAX_XTRA_PARA);
    printf("    Initial (relative) SS value:     %" PRIuLEAST16 "\n",     x->INITIAL_SS_VALUE);
    printf("    Initial SP value:                0x%04" PRIx16 "\n",      x->SP_VALUE);
    printf("    Initial IP value:                %" PRIuLEAST16 "\n",     x->IP_VALUE);
    printf("    Initial (relative) CS value:     %" PRIuLEAST16 "\n",     x->INIT_CS_VALUE);
    printf("    Address of relocation table:     0x%04" PRIx16 "\n",      x->ADDR_RELOC);
    printf("    Overlay number:                  %" PRIuLEAST16 "\n",     x->OVERLAY_NUM);
    printf("    OEM identifier:                  %" PRIuLEAST16 "\n",     x->OEM_ID);
    printf("    OEM information:                 %" PRIuLEAST16 "\n",     x->OEM_INFO);
    printf("    PE header offset:                0x%04" PRIx16 "\n",      x->PE_HEADER_OFFSET);
    printf("\n");
}


void updateCOFF(struct COFF *y, enum coff state1, int update){

    switch(state1){
        case MACH    : y->MACHINE = (short)update;
                       break;
        case SECTION : y->NUM_OF_SEC = update;
                       break;
        case DATE    : y->DATE_STAMP = update;
                       break;
        case SYM_OFF : y->SYM_OFFSET = update;
                       break;
        case numSYM  : y->NUM_SYM = update;
                       break;
        case sizeHEAD: y->SIZE_HEAD = update;
                       break;
        case CHARC   : y->CHAR = update;
                       break;
        default      : break;
    }

    #ifdef DEBUG
    /*printf("UPDATED Struct:\n");
    printf("Updating DATA #%d\n",state1);
    coff_print(temp);
    printf("\n");*/ //@TODO WILL FIX DEBUG Later
    #endif
}

void coff_print(struct COFF *y){
    printf("COFF/FILE Header:\n");
    printf("    Machine:                            0x%04" PRIx16 " %s\n",  y->MACHINE, (printMachine(y->MACHINE)));
    printf("    Number of sections:                 %" PRIuLEAST16 "\n",    y->NUM_OF_SEC);
    printf("    Date/time stamp:                    %" PRIuLEAST32 " %s",   y->DATE_STAMP, (printDate(y->DATE_STAMP)));
    printf("    Symbol Table offset:                %" PRIuLEAST32 "\n",    y->SYM_OFFSET);
    printf("    Number of Symbols:                  %" PRIuLEAST32 "\n",    y->NUM_SYM);
    printf("    Size of optional header:            0x%02" PRIx16 "\n",     y->SIZE_HEAD);
    printf("    Characteristics:                    0x%04" PRIx16 "\n",     y->CHAR);
    printf("    Characteristics names:\n");
    printChar(y->CHAR);
    printf("\n");
}

//@TODO IMPLEMENT OPT FUNCTION under updateStruct
void updateOPT(struct OPT *x, enum opt state, int update){

    switch(state){
        case MAG_NUM      : if(update == 0x20b || update == 0x10b)
                                x->MN = update;
                            else{
                                printf("readpe: UNKNOWN FILETYPE");
                                exit(0);
                            }
                            break;
        case MAJ_LINK     : x->majLINK = update;
                            break;
        case MIN_LINK     : x->minLINK = update;
                            break;
        case TEXT_SIZE    : x->sizeText = update;
                            break;
        case DATA_SIZE    : x->sizeData = update;
                            break;
        case BSS_SIZE     : x->sizeBSS = update;
                            break;
        case ENTRY_PT     : x->entryPT = update;
                            break;
        case TEXT_ADDR    : x->textADDR = update;
                            break;
        case DATA_ADDR    : x->dataADDR = update;
                            break;
        case IMG_BASE     : x->imgBase = update;
                            break;
        case ALIGN_SEC    : x->sectionAlign = update;
                            break;
        case ALIGN_FILE   : x->alignFactor = update;
                            break;
        case MAJ_OS       : x->majOS = update;
                            break;
        case MIN_OS       : x->minOS = update;
                            break;
        case MAJ_IMG      : x->majImg = update;
                            break;
        case MIN_IMG      : x->minImg = update;
                            break;
        case MAJ_SUB      : x->majSub = update;
                            break;
        case MIN_SUB      : x->minSub = update;
                            break;
        case SIZE_IMG     : x->sizeImg = update;
                            break;
        case SIZE_HEAD    : x->sizeHead = update;
                            break;
        case CKSUM        : x->cksum = update;
                            break;
        case SUBSYS       : x->subReq = update;
                            break;
        case DLL_CHAR     : x->dllChar = update;
                            break;
        case SIZE_stackRES: x->stackRes = update;
                            break;
        case SIZE_stackCOM: x->stackCom = update;
                            break;
        case SIZE_heapRES : x->heapRes = update;
                            break;
        case SIZE_heapCOM : x->heapCom = update;
                            break;
        case END_OPT      : break;
        default           : break;
    }

    #ifdef DEBUG
    /*printf("UPDATED Struct:\n");
    printf("Updating DATA #%d\n",state);
    opt_print(temp);
    printf("\n");*/
    #endif
}
void opt_print(struct OPT *x){
    printf("Optional/Image Header:\n");
    printf("    Magic Number:                 0x%03" PRIx16 " ",     x->MN); //@TODO PRINT MAGIC NUMBER
    if(x->MN == 0x10b) printf("%s\n",MAG.OPT_MN1);
    else              printf("%s\n",MAG.OPT_MN2);
    printf("    Linker major version:         %" PRIuLEAST16 "\n",    x->majLINK);
    printf("    Linker minor version:         %" PRIuLEAST16 "\n",    x->minLINK);
    printf("    Size of .text section:        0x%04" PRIx16 "\n",     x->sizeText);
    printf("    Size of .data section:        0x%04" PRIx16 "\n",     x->sizeData);
    printf("    Size of .bss section:         %" PRIuLEAST16 "\n",    x->sizeBSS);
    printf("    Entrypoint:                   0x%04" PRIx16 "\n",     x->entryPT);
    printf("    Address of .text section:     0x%04" PRIx16 "\n",     x->textADDR);
    printf("    Address of .data section:     0x%04" PRIx16 "\n",     x->dataADDR);
    printf("    ImageBase:                    0x%06" PRIx32 "\n",     x->imgBase);
    printf("    Alignment of sections:        0x%04" PRIx16 "\n",     x->sectionAlign);
    printf("    Alignment factor:             0x%03" PRIx16 "\n",     x->alignFactor);
    printf("    Major version of required OS: %" PRIuLEAST16 "\n",    x->majOS);
    printf("    Minor version of required OS: %" PRIuLEAST16 "\n",    x->minOS);
    printf("    Major version of image:       %" PRIuLEAST16 "\n",    x->majImg);
    printf("    Minor version of image:       %" PRIuLEAST16 "\n",    x->minImg);
    printf("    Major version of subsystem:   %" PRIuLEAST16 "\n",    x->majSub);
    printf("    Minor version of subsystem:   %" PRIuLEAST16 "\n",    x->minSub);
    printf("    Size of image:                0x%04" PRIx16 "\n",     x->sizeImg);
    printf("    Size of headers:              0x%03" PRIx16 "\n",     x->sizeHead);
    printf("    Checksum:                     %" PRIuLEAST16 "\n",     x->cksum);
    printf("    Subsystem required:           0x%01" PRIx16 "",     x->subReq); //@TODO SUBSYS
    if(x->subReq == 3)
        printf(" (%s)\n",recSUB);
    printf("    DLL Characteristics:          0x%04" PRIx16 "\n",     x->dllChar);
    printf("    DLL characteristics names:\n"); //@TODO PRINT CHARAC
    printChar_OPT(x->dllChar);
    printf("    Size of stack to reserve:     0x%06" PRIx32 "\n",     x->stackRes);
    printf("    Size of stack to commit:      0x%04" PRIx16 "\n",     x->stackCom);
    printf("    Size of heap to reserve:      0x%06" PRIx32 "\n",     x->heapRes);
    printf("    Size of heap to commit:       0x%04" PRIx16 "\n",     x->heapCom);
    printf("\n");
}

void update_Sect(struct Sect* sectHead,enum sect state,int update){
    switch(state){
        case virtSize   :   sectHead->VIRT_SIZE = update;
                            break;
        case virtAddr   :   sectHead->VIRT_ADD = update;
                            break;
        case sizeRawData:   sectHead->SIZE_RAW_DATA = update;
                            break;
        case ptrRawData :   sectHead->PTR_RAW_DATA = update;
                            break;
        case numReloc   :   sectHead->NUM_OF_RELOC = update;
                            break;
        case sectChars  :   sectHead->CHARS = update;
        default         :   break;
    }
    
    #ifdef DEBUG
    printf("UPDATED Struct:\n");
    printf("Updating DATA #%d\n",state);
    section_print(sectHead);
    printf("\n");
    #endif
}

void section_print(struct Sect* sectHead){
    printf("    Section\n");
    printf("        Name:                       %s\n",sectHead->sectName); //@TODO NAME OF SECTION
    printf("        Virtual Size:               0x%03" PRIx32 " (%d bytes)\n", sectHead->VIRT_SIZE,sectHead->VIRT_SIZE); //@TODO BYTES
    printf("        Virtual Addresss:           0x%04" PRIx32 "\n",sectHead->VIRT_ADD);    
    printf("        Size of Raw Data:           0x%04" PRIx32 " (%d bytes)\n",sectHead->SIZE_RAW_DATA,sectHead->SIZE_RAW_DATA); //@TODO BYTES
    printf("        Pointer to Raw Data:        0x%03" PRIx32 "\n",sectHead->PTR_RAW_DATA);
    printf("        Number Of Relocations:      %" PRIuLEAST16 "\n",sectHead->NUM_OF_RELOC);
    printf("        Characteristics:            0x%06" PRIx32 "\n",sectHead->CHARS);
    printf("        Characteristic Name:\n"); //@TODO PRint NAM'
    sec_PrintChar(sectHead->CHARS);
    printf("\n");
}
