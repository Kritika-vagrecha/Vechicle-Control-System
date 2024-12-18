/*  Can1 Interrupt  */
#include <LPC21xx.H>
#include"header.h"

extern unsigned char flag;
extern CAN2 v1;
void can2_rx_handler(void) __irq{
	v1.id=C2RID;
	v1.dlc=(C2RFS>>16)&0x0F;
	v1.rtr=(C2RFS>>30)&1;
	if(v1.rtr==0){				//if dataframe is received
		v1.byteA=C2RDA;
		v1.byteB=C2RDB;
	}
	C2CMR=(1<<2);					//release rx buff
 	flag=1;
	VICVectAddr=0;
}

void config_vic_for_can2(void){
	VICIntSelect=0;
	VICVectCntl2=27|(1<<5);
	VICVectAddr2=(unsigned int)can2_rx_handler;
	VICIntEnable|=(1<<27);
}
void en_can2_interrupt(void){
	C2IER=1;				//enable CAN rx interrupt
} 
