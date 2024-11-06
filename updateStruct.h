
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "MSDOSHeader.h"
#include "state.h"
#include "COFFHeader.h"
#include "OPTHeader.h"
#include "SectionHeader.h"


#ifndef UPDATESTRUCT_H
#define UPDATESTRUCT_H
void updateMS(struct MSDOS* x,enum msdos state,int update);
void ms_print(struct MSDOS* x);


void updateCOFF(struct COFF* y,enum coff state1,int update);
void coff_print(struct COFF* y);

//@TODO IMPLEMENT OPT HEADER
void updateOPT(struct OPT* z,enum opt state,int update);
void opt_print(struct OPT* z);

//@TODO Section HEADERS
void update_Sect(struct Sect* abc,enum sect state, int update);
void section_print(struct Sect* abc);
#endif
