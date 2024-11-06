
#include "COFFHeader.h"

const char* MACH32 =    "IMAGE_FILE_MACHINE_I386";
const char* MACH64 =    "IMAGE_FILE_MACHINE_AMD64";
const char* CHARBYTE1 = "IMAGE_FILE_EXECUTABLE_IMAGE";
const char* CHARBYTE2 = "IMAGE_FILE_LARGE_ADDRESS_ AWARE";
const char* CHARBYTE3 = "IMAGE_FILE_32BIT_MACHINE";
const char* undef = "UNKNOWN";

const char * printMachine(int data){
    switch(data){
        case  0x14c : return MACH32;
                      break;
		case 0x8664 : return MACH64;
		      		  break; 
		default     : return undef;
                      break;
    }
}

void printChar(int data){
    //Using BitWise Functions we can get the specific byte
    for(unsigned int n=0 ; n<3 ; n++){
    	int x = (data >> (4*n)) & 0xf;
	switch(n){
        	case 0 : if(x == 0x2)
						printf("%64s\n",CHARBYTE1);
                	 break;
        	case 1 : if(x == 0x2)
						printf("%64s\n",CHARBYTE2);
                     break;
			case 2 : if(x == 0x1)
						printf("%64s\n",CHARBYTE3);
			 	     break;
            default: break;
    	}
    }
}

const char * printDate(int data){
    time_t epoch = data;
    struct tm* info;

    info = gmtime(&epoch);
    return (asctime(info));

}
