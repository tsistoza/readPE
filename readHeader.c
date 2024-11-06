
#include "readHeader.h"
//All Functions work similar with few modifications such as the state machine

int readMS(unsigned char* f,int address,struct MSDOS *dosHead){
    
    //Setup State Machine
    enum msdos check_stateMS = MAGIC;
    enum msdos state1        = MAGIC;
    unsigned char hex[21];
    int index= 0;
    int addr = address;
    int base = address;
    unsigned int data;

    for (int i=0 ; i < 0x3F ; i++){                    //0x3E is where MSDOS Header ends
         state1 = find_StateMSDOS(i,state1,base);

         //If state changed store Data.
         if(check_stateMS != state1){

             int size = sizeSectionMS(state1-1);
             hex[size] = '\0';

             //STORE DATA INTO CHAR ARRAY
             for(int j=i-1 ; j!=i-1-size ; j--){
                unsigned char c = (unsigned char) f[j];
                hex[index] = c;
                index++;
    	      }

             //IGNORE ANY STATES WITH X
             if(state1-1 != X1 && state1-1 != X2 && state1-1 != X3){
    	 	      data = hexbyte(hex,size);                 //Turn Hex to String

    	      }
    	      else
    		      data=0;

             updateMS(dosHead,state1-1,data);           //Update struct with data
             check_stateMS = state1;                    //Update Check_state for next iteration
             index = 0;
         }
          addr = Relative_Address(addr);              //Update relative address
       } //for()
    return addr-1;
}

int readCOFF(unsigned char* f,struct MSDOS *dosHead,struct COFF *coffHead){

    //Setup State Machine
    enum coff stateCOFF       = MACH;
    enum coff check_stateCOFF = MACH;
    int addr = dosHead->PE_HEADER_OFFSET+4;
    int base = dosHead->PE_HEADER_OFFSET;
    int index=0;
    unsigned char hex[21];
    unsigned int data;

   for(int i=addr ; i<0x119 ; i++){
          stateCOFF = find_StateCOFF(i,stateCOFF,base);
          
          if(check_stateCOFF != stateCOFF){
             int size = sizeSectionCOFF(stateCOFF-1);
             hex[size] = '\0';

             for(int j=i-1 ; j!=i-1-size ; j--){
                unsigned char c = (unsigned char) f[j];
                hex[index] = c;
                index++;
    	      }

             data = hexbyte(hex,size);
             updateCOFF(coffHead,stateCOFF-1,data);
             check_stateCOFF = stateCOFF;
             index=0;
         }
          addr = Relative_Address(addr);
   }
   return addr-1;
}

int readOPT(unsigned char* f,int address,struct OPT *optHead){
    
    //Setup State Machine
    enum opt stateOPT       = MAG_NUM;
    enum opt check_stateOPT = MAG_NUM;
    int addr    = address;
    int addrend = address+97; //PE32 -> ends here
    int base    = address;
    int index=0,value=0;
    unsigned char hex[21];
    unsigned int data;

    for(int i=addr ; i<addrend ; i++){
      stateOPT = find_StateOPT(i,stateOPT,base,value);

      if(check_stateOPT != stateOPT){
         int size = sizeSectionOPT(stateOPT-1,value);
         hex[size] = '\0';
         
         for(int j=i-1 ; j!=i-1-size ; j--){
            unsigned char c = (unsigned char) f[j];
            hex[index] = c;
            index++;
         }

         data = hexbyte(hex,size);
         updateOPT(optHead,stateOPT-1,data);
         check_stateOPT = stateOPT;
         index=0;
      }

      value = optHead->MN;
      if(value == 0x20b)          //Set addrend if PE32+
         addrend = base+117;

      addr = Relative_Address(addr);
   }
   return addr-1;
}

int readSectionHead(int addr,struct Sect* sectHead,unsigned char* f){
   
   //Setup State Machine
   int  temp=addr;
   enum sect stateSect       = sectHeader;
   enum sect check_stateSect = sectHeader;
   int  addrend = addr+41;
   int  base = addr;
   int  index=0;
   unsigned char hex[21];
   unsigned int  data;

   for( ; temp<=addr+8 ; temp++){
      stateSect = find_StateSECT(temp,stateSect,base); //For The Name of Section
      sectHead->sectName[index] = f[temp];
      check_stateSect = stateSect;
      index++;
   }
   index=0;

   for( ; temp<addrend ; temp++){
      stateSect = find_StateSECT(temp,stateSect,base); //Find State

      if(check_stateSect != stateSect){
         int size = sizeSectionHeader(stateSect-1);
         hex[size] = '\0';

         for(int j=temp-1 ; j != temp-1-size ; j--){ //Collect Data
            unsigned char c = (unsigned char) f[j];
            hex[index] = c;
            index++;
         }

         data = hexbyte(hex,size);
         update_Sect(sectHead,stateSect-1,data);
         check_stateSect = stateSect;
         index=0;
      }
   }
   return temp-1;
}