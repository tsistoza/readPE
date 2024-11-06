
#include <stdio.h>
#include "state.h"

#ifndef SectionSize_H
#define SectionSize_H

int sizeSectionMS(enum msdos state);

//@TODO sizeSectionCOFF() Function
int sizeSectionCOFF(enum coff state);

int sizeSectionOPT(enum opt state,int value);

int sizeSectionHeader(enum sect state);

#endif