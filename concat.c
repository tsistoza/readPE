
#include "concat.h"
#include <string.h>
#include <stdlib.h>

int hexbyte(unsigned char* str,int size){

    unsigned char hexdata[21];
    int loop=0;
    int i=0;
    
    //Turn String of Char to Hex String
    while(str[loop] != '\0' || size>0){  //Added size because Sometimes string starts with 00(NULL)
        sprintf((char*)(hexdata+i),"%02X", str[loop]);
        loop+=1;
        i+=2;
	    size--;
    }
    //insert NULL at the end of the output string
    hexdata[i++] = '\0';

    //Return Hex String to Int
    return strtol((char*)hexdata, NULL, 16);
}
