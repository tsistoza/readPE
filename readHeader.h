
#include <stdio.h>            //printf
#include "relative_address.h" //Used to update address
#include "MSDOSHeader.h"      //Used to store data for MSDOS Header
#include "COFFHeader.h"       //Used to store data for COFF Header
#include "OPTHeader.h"        //Used to store data for OPT Header
#include "state.h"            //Used to help navigate through .exe file
#include "updateStruct.h"     //Print out struct data, and modify struct data
#include "concat.h"           //Concatenate Hexstring
#include "SectionSize.h"      //Returns size of section

#ifndef  readHeader_H
#define  readHeader_H

int readMS(unsigned char* f,int address,struct MSDOS *dosHead);
int readCOFF(unsigned char* f,struct MSDOS *dosHead,struct COFF *coffHead);
int readOPT(unsigned char* f,int address,struct OPT *optHead);
int readSectionHead(int addr,struct Sect* abc,unsigned char* f);

#endif