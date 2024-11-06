
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef SectionHeader_H
#define SectionHeader_H

struct Sect{
    char sectName[9];
    uint32_t VIRT_SIZE;
    uint32_t VIRT_ADD;
    uint32_t SIZE_RAW_DATA;
    uint32_t PTR_RAW_DATA;
    //uint32_t PTR_RELOC;
    //uint32_t PTR_LINE_NUM;
    uint16_t NUM_OF_RELOC;
    //uint16_t NUM_OF_LINE;
    uint32_t CHARS;
};
void sec_PrintChar(int data);

#endif