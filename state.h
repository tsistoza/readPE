
#ifndef STATE_H
#define STATE_H
#include <stdio.h>

enum msdos {MAGIC
          ,BYTES
          ,PAGES
          ,RELOC
          ,HEAD
          ,MIN_XTRA
          ,MAX_XTRA
          ,INIT_SS
          ,INIT_SP
          ,X1 //X means dont care (Sections not included in prints)
          ,INIT_IP
          ,INIT_CS
          ,ADDR_RELOC
          ,OVERLAY
          ,X2
          ,OEM_ID
          ,OEM_info
          ,X3
          ,PE_HEAD
          ,XTRA};

enum coff{MACH
        ,SECTION
        ,DATE
        ,SYM_OFF
        ,numSYM
        ,sizeHEAD
        ,CHARC
        ,XTR};

enum opt{MAG_NUM
        ,MAJ_LINK
        ,MIN_LINK
        ,TEXT_SIZE
        ,DATA_SIZE
        ,BSS_SIZE
        ,ENTRY_PT
        ,TEXT_ADDR
        ,DATA_ADDR
        ,IMG_BASE
        ,ALIGN_SEC
        ,ALIGN_FILE
        ,MAJ_OS
        ,MIN_OS
        ,MAJ_IMG
        ,MIN_IMG
        ,MAJ_SUB
        ,MIN_SUB
        ,Y1     //Y MEANS DONT CARE
        ,SIZE_IMG
        ,SIZE_HEAD
        ,CKSUM
        ,SUBSYS
        ,DLL_CHAR
        ,SIZE_stackRES
        ,SIZE_stackCOM
        ,SIZE_heapRES
        ,SIZE_heapCOM
        ,Y2
        ,Y3
        ,END_OPT};

enum sect{sectHeader
         ,virtSize
         ,virtAddr
         ,sizeRawData
         ,ptrRawData
         ,ptrReloc
         ,ptrLine
         ,numReloc
         ,numLineNum
         ,sectChars
         ,endSect};

enum msdos find_StateMSDOS(int addr,enum msdos state,int offset);
enum coff  find_StateCOFF(int addr,enum coff state,int offset);
enum opt   find_StateOPT(int addr,enum opt state,int offset,int value);
enum sect  find_StateSECT(int addr,enum sect state,int offset);
#endif