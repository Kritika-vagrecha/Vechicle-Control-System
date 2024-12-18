/*  CAN2 Body Control Module  */
#include"header.h"
#include <LPC21xx.H>

#define head ((IOPIN0>>14)&1)			//switch for headlight
#define left ((IOPIN0>>15)&1)			//switch for left indicator
#define right ((IOPIN0>>16)&1)			//switch for right indicator

CAN2 v;
int main(){
	
	can2_init();
	IODIR0=(1<<17);

	v.rtr=0;
	v.dlc=1;
	v.byteB=0;

	while(1){
		if(head==0){
			while(head==0);
			v.id=0x200;
			v.byteA=0x10;
			can2_tx(v);
		}
		if(left==0){
			while(left==0);
			v.id=0x201;
			v.byteA=0x11;
			can2_tx(v);
		}
		if(right==0){
			while(right==0);
			v.id=0x202;
			v.byteA=0x12;
			can2_tx(v);
		}
	}
}
