
//For the MSDOS Header Struct
/* 15 Vars in Total                            LENGTH:    OFFSET:
 *Magic number:                    0x5a4d (MZ) WORD       0
    Bytes in last page:              144       WORD       2
    Pages in file:                   3         WORD       4
    Relocations:                     0         WORD       6
    Size of header in paragraphs:    4         WORD       8
    Minimum extra paragraphs:        0         WORD       A
    Maximum extra paragraphs:        65535     WORD       C
    Initial (relative) SS value:     0         WORD       E
    Initial SP value:                0xb8      WORD       10
    Checksum                                   WORD       12
    Initial IP value:                0         WORD       14    
    Initial (relative) CS value:     0         WORD       16
    Address of relocation table:     0x40      WORD       18
    Overlay number:                  0         WORD       1A
    Reserved Words                             WORD*4     1C
    OEM identifier:                  0         WORD       24
    OEM information:                 0         WORD       26
    Reserved Words:                            WORD*10    28
    PE header offset:                0x100     WORD       3C
 */
 #include <inttypes.h>
#ifndef MSDOSHEADER_H
#define MSDOSHEADER_H

struct MSDOS{
   uint16_t   MAGIC_NUM;
   uint16_t   BYTES_LAST_PAGE;
   uint16_t   PAGES_IN_FILE;
   uint16_t   RELOCATIONS;
   uint16_t   SIZE_OF_HEADER_IN_PARAGRAPHS;
   uint16_t   MIN_XTRA_PARA;
   uint16_t   MAX_XTRA_PARA;
   uint16_t   INITIAL_SS_VALUE;
   uint16_t   SP_VALUE;
   uint16_t   IP_VALUE;
   uint16_t   INIT_CS_VALUE;
   uint16_t   ADDR_RELOC;
   uint16_t   OVERLAY_NUM;
   uint16_t   OEM_ID;
   uint16_t   OEM_INFO;
   uint16_t   PE_HEADER_OFFSET;
};

#endif
