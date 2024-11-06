
#include "SectionHeader.h"

struct secChars{
    const char* char1;
    const char* char2;
    const char* char3;
    const char* char4;
    const char* char5;
    const char* char6;
} sects =  {.char1 = "IMAGE_SCN_CNT_CODE"
           ,.char2 = "IMAGE_SCN_CNT_INITIALIZED_DATA"
           ,.char3 = "IMAGE_SCN_MEM_DISCARDABLE"
           ,.char4 = "IMAGE_SCN_MEM_READ"
           ,.char5 = "IMAGE_SCN_MEM_WRITE"
           ,.char6 = "IMAGE_SCN_MEM_EXECUTE"};

//USING BITWISE FUNCTION WE CAN FIND CHARACTERISTICS
void sec_PrintChar(int data){
    for(unsigned int n=0 ; n<8 ; n++){
    	int x = (data >> (4*n)) & 0xf; //Grab nth byte from data
    
        switch(n){

            case 1: for(int j=3 ; j>0 ; j--){
                        int bit = (x >> j) & 0x1; //Mask OFF every bit except one.
                        switch(j){
                            case 1: if(bit == 1)
                                        printf(" %70s\n",sects.char1);
                                    break;
                            case 2: if(bit == 1)
                                        printf(" %70s\n",sects.char2);
                                    break;
                            default:break;
                        }
                    } //for() bit
                    break;
            
            case 6: if(x == 2)
                        printf(" %70s\n",sects.char3);
                    break;
            
            case 7: for(int j=3 ; j>0 ; j--){
                        int bit = (x >> j) & 0x1;
                        switch(j){
                            case 1: if(bit == 1)
                                        printf(" %70s\n",sects.char6);
                                    break;
                            case 2: if(bit == 1)
                                        printf(" %70s\n",sects.char4);
                                    break;
                            case 3: if(bit == 1)
                                        printf(" %70s\n",sects.char5);
                                    break;
                            default:break;
                        }
                    } //for() BIT
                    break;

            default:break;

        } //switch() BYTE
    } //for() BYTE
}
