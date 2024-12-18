/*  CAN2 Driver  */
#include <LPC21xx.H>
#include"header.h"

unsigned int *ptr=(unsigned int*)0xE0038000;

void can2_init(){
	PINSEL1|=0x00014000;		
	VPBDIV=1;					//PCLK=60MHz
	C2MOD=1;					//Select Reset mode
	C2BTR=0x001C001D;			//125 kbps baud

//	AFMR=2;						//Accept all msgs
//-------------------------------------------------------------------------
/*---- Vehicle Control Module AFMR ----*/
 
//---- For H/W ----
	ptr[0]=0x22002201;			//H-ID=200 & L-ID=201
    //0010 0010 | 0000 0000 | 0010 0010 | 0000 0001

	ptr[1]=0x22021000;			//R-ID=202
    //0010 0010 | 0000 0010 | 0001 0000 | 0000 0000

////---- For INI Scripting ----
//	*(ptr+0)=0x42004201;		//H-ID=200 & L-ID=201
//	0100 0010 | 0000 0000 | 0100 0010 | 0000 0001
//
//	*(ptr+1)=0x42021000;		//R-ID=202	 
//	0100 0010 | 0000 0010 | 0001 0000 | 0000 0000
	
	SFF_sa=0;
	SFF_GRP_sa=0x8;				 
	EFF_sa=EFF_GRP_sa=0x8;					
	ENDofTable=0x8;						  

//--------------------------------------------------------------------------
/*---- Reverse Car Parking Module AFMR ----*/

////---- For H/W ----
//	*(ptr+0)=0x22FA22FB;			//Reverse Gear-ID -- ON=2FA & OFF=2FB
//    //0010 0010 | 1111 1010 | 0010 0010 | 1111 1011

////---- For INI Scripting ----
//	*(ptr+0)=0x42FA42FB;		//Reverse Gear-ID -- ON=2FA & OFF=2FB
//    //0100 0010 | 1111 1010 | 0100 0010 | 1111 1011

//	SFF_sa=0;
//	SFF_GRP_sa=0x4;				 
//	EFF_sa=EFF_GRP_sa=0x4;					
//	ENDofTable=0x4;						 
	
	AFMR=0;						//Accept all msgs is OFF OR Enable AFMR Settings
	C2MOD=0;					//Cancel Reset mode
}

#define TCS ((C2GSR>>3)&1)
void can2_tx(CAN2 v){
	C2TFI1=(v.dlc<<16);			//set dlc & rtr == 0
	C2TID1=v.id;
	if(v.rtr==0){				//if data frame
		C2TDA1=v.byteA;
		C2TDB1=v.byteB;
	}
	else						//if remote frame
		C2TFI1|=(1<<30);		//rtr=1
	C2CMR=1|(1<<5);				//start transmission
	while(TCS==0);
}

#define RBS (C2GSR&1)
void can2_rx(CAN2 *ptr){
	while(RBS==0);
	ptr->id=C2RID;
	ptr->dlc=(C2RFS>>16)&0x0F;
	ptr->rtr=(C2RFS>>30)&1;
	if(ptr->rtr==0){			//if dataframe is received
		ptr->byteA=C2RDA;
		ptr->byteB=C2RDB;
	}
	C2CMR=(1<<2);				//release rx buff
}
