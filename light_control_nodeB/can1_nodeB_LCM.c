/*  CAN2 Light Control Module  */
#include"header.h"
#include <LPC21xx.H>

#define LED (7<<17)	 		//---> for output direction
#define HLED (1<<17)		//---> for Headlight

CAN1 v1;
extern unsigned char l,r;
unsigned char h;			//---> flags for headlight, left indicator, right indicator
unsigned char flag;			//---> to monitor interrupt
main(){
 	IODIR0=LED;
	IOSET0=LED;
	
	can1_init();
	uart0_init(9600);
	uart0_tx('Y');

	config_vic_for_can1();
	en_can1_interrupt();

	config_vic_for_timer1();
	en_timer1_interrupt();
	
	h=l=r=0;
	while(1){
		if(flag){
			flag=0;
			if(v1.byteA==0x10){
				uart0_tx('H');
				h=!h;				//--> toggle headlight flag
				if(h){
					IOCLR0=HLED;
				}
				else{
					IOSET0=HLED;
				}
			}

			if(v1.byteA==0x11){		//--> toggle left indicator flag
				uart0_tx('L');
				l=!l;
				if(r){
					T1TC=0;
					r=!r;
				}
				else{
					if(l){
						T1TC=0;
						T1TCR=1;
					}
					else{
						T1TC=0;
						T1TCR=0;
					}
				}
			}
			if(v1.byteA==0x12){		//--> toggle right indicator flag
				uart0_tx('R');
				r=!r;
				if(l){
					T1TC=0;
					l=!l;
				}
				else{
					if(r){
						T1TC=0;
						T1TCR=1;
					}
					else{
						T1TC=0;
						T1TCR=0;
					}
				}
			}
		}
	}
}
