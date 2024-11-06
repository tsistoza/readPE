#include <stdio.h>            //printf
#include <stdlib.h>           //exit perros
#include <fcntl.h>            //mmap
#include <sys/types.h>        //mmap
#include <sys/stat.h>         //mmap
#include <unistd.h>           //mmap
#include <sys/io.h>           //mmap
#include <sys/mman.h>         //mmap
#include <string.h>           //String OPS
#include <inttypes.h>         //for uints

#include "relative_address.h" //Used to update address
#include "MSDOSHeader.h"      //Used to store data for MSDOS Header
#include "COFFHeader.h"       //Used to store data for COFF Header
#include "OPTHeader.h"        //Used to store data for OPT Header
#include "SectionHeader.h"    //Used to store data for Section Header
#include "state.h"            //Used to help navigate through .exe file
#include "updateStruct.h"     //Print out struct data, and modify struct data
#include "concat.h"           //Concatenate Hexstring
#include "SectionSize.h"      //Returns size of section
#include "readHeader.h"       //Data Collecting

int main(int argc, char * argv[]){
   
   if(argc < 2){
	   printf("readpe: No File Specified\n");
   	exit(1);
   }

   //Using MMAP to open file
   unsigned char *f;
   struct stat s;
   const char * file_name = argv[1];
   int fd = open(file_name,O_RDONLY);
   if(fd == -1){
	   perror("readpe: FILE NOT FOUND\n");
   	exit(1);
   }
   
   //Getting Size of File
   int status = fstat(fd,&s);
   if(status == -1){
   	perror("readpe: FILE NOT FOUND\n");
      exit(1);
   }
   int size = s.st_size;

   //Memory Map File
   f = (unsigned char *) mmap (0,size,PROT_READ,MAP_PRIVATE,fd,0);

   struct MSDOS *dosHead  = malloc(sizeof(struct MSDOS));
   struct COFF  *coffHead = malloc(sizeof(struct COFF));
   struct OPT   *optHead  = malloc(sizeof(struct OPT));

   int address = 0; //Start From Beginning of File

   //Store Data into the Structs
   address = readMS(f,address,dosHead);           //@TODO Validate Data for Magic Numbers
   address = readCOFF(f,dosHead,coffHead);
   address = readOPT(f,address,optHead);

   while(f[address] != 0x2E) //GOTO Sections Headers
      address++;


   //Section Headers
   struct Sect *sectHead[coffHead->NUM_OF_SEC]; //Section Header Struct
   for(int i=0 ; i<coffHead->NUM_OF_SEC ; i++){
      sectHead[i] = malloc(sizeof(struct Sect));
      address = readSectionHead(address,sectHead[i],f);  
   }

   //PRINT OUT RESULTS
   ms_print(dosHead);
   coff_print(coffHead);
   opt_print(optHead);
   printf("Section Headers:\n");
   for(int i=0 ; i<coffHead->NUM_OF_SEC ; i++){
      section_print(sectHead[i]);
      free(sectHead[i]);
   }
   free(dosHead);
   free(coffHead);
   free(optHead);
   
   //UNMAP and Close
   int err = munmap(f,s.st_size);
   if(err == -1)
   	perror("Unmapping Failed\n");
   close(fd);

   return 0;
}//main()
