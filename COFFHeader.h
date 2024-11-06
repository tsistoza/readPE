
//Make a struct with the COFF File Sections
/*
COFF/File header                                                                   Length:   OFFSET:
    Machine:                         0x14c IMAGE_FILE_MACHINE_I386                 WORD      PE+4
    Number of sections:              5                                             WORD      PE+6
    Date/time stamp:                 1680137846 (Thu, 30 Mar 2023 00:57:26 UTC)    DWORD     PE+8
    Symbol Table offset:             0                                             DWORD     PE+12
    Number of symbols:               0                                             DWORD     PE+16
    Size of optional header:         0xe0                                          WORD      PE+20
    Characteristics:                 0x102                                         WORD      PE+22
    Characteristics names
                                         IMAGE_FILE_EXECUTABLE_IMAGE
                                         IMAGE_FILE_32BIT_MACHINE
                                         */
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#ifndef COFFHeader_H
#define COFFHeader_H

struct COFF{
   uint16_t MACHINE;
   uint16_t NUM_OF_SEC;
   uint32_t DATE_STAMP;
   uint32_t SYM_OFFSET;
   uint32_t NUM_SYM;
   uint16_t SIZE_HEAD;
   uint16_t CHAR;
};
const char * printMachine(int data);
void printChar(int data);
const char * printDate(int data);
#endif
