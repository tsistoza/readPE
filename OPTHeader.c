
#include "OPTHeader.h"

struct OPTCHARS{
    const char* char1;
    const char* char2;
    const char* char3;
} optionalchar = {.char1 = "IMAGE_DLL_CHARACTERISTICS_DYNAMIC_BASE"
                 ,.char2 = "IMAGE_DLL_CHARACTERISTICS_NX_COMPAT"
                 ,.char3 = "IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE"};

void printChar_OPT(int data){
    for(unsigned int n=0 ; n<4 ; n++){
    	int x = (data >> (4*n)) & 0xf; //grab the nth byte
        switch(n){
            case 1: for(int j=3 ; j>0 ; j--){ //grab the nth bit from byte
                        int bit = (x >> j) & 0x1;
                        switch(j){
                            case 2:  if(bit)
                                        printf(" %70s\n",optionalchar.char1);
                                     break;
                            default: if(bit){
                                        bit = bit << (j+(n*4));
                                        printf(" %55s UNKNOWN [0x%02x]\n","",bit);
                                     }
                                     break;
                        }//SWITCH() BIT
                    } //FOR() BIT
                    break;
            case 2: if(x == 1)
                        printf(" %70s\n",optionalchar.char2);
                    break;
            case 3: if(x == 8)
                        printf(" %70s\n",optionalchar.char3);
                    break;
            default: break;
        }
    }
}
