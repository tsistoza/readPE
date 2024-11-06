
#include <stdio.h>
#include <inttypes.h>
#ifndef OPTHeader_H
#define OPTHeader_H
// NOTE OPT HEADER STARTS RIGHT AFTER COFFHEADER SET OFFSET = ADDR AFTER END OF COFF DATA COLLECTION
struct OPT{
    uint16_t MN;
    uint16_t majLINK;
    uint16_t minLINK;
    uint16_t sizeText;
    uint16_t sizeData;
    uint16_t sizeBSS;
    uint16_t entryPT;
    uint16_t textADDR;
    uint16_t dataADDR;
    uint32_t imgBase;
    uint16_t sectionAlign;
    uint16_t alignFactor;
    uint16_t majOS;
    uint16_t minOS;
    uint16_t majImg;
    uint16_t minImg;
    uint16_t majSub;
    uint16_t minSub;
    uint16_t sizeImg;
    uint16_t sizeHead;
    uint16_t cksum;
    uint16_t subReq;
    uint16_t dllChar;
    uint32_t stackRes;
    uint16_t stackCom;
    uint32_t   heapRes;
    uint16_t heapCom;
};
//@TODO IMPLEMENT OPT print STR functions
void printChar_OPT(int data);

#endif