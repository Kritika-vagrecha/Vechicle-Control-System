#include<lpc21xx.h>
#include"header.h"

#define LLED (1<<18)		//---> for Left Indicator
#define RLED (1<<19)		//---> for Right Indicator
#define BUZ (1<<21)	  		//---> for buzzer

unsigned char l,r;
unsigned char ll,rr;

/*  ISR for LCM program  */
void timer1_handler(void) __irq{
	if(l){
		if(ll){
			IOCLR0|=LLED;
			IOSET0|=BUZ;
			ll=!ll;
		}
		else{
			IOSET0|=LLED;
			IOCLR0|=BUZ;
			ll=!ll;
		}
	}
	if(r){
		if(rr){
			IOCLR0|=RLED;
			IOSET0|=BUZ;
			rr=!rr;
		}
		else{
			IOSET0|=RLED;
			IOCLR0|=BUZ;
			rr=!rr;
		}
	}
	T1IR=1;
	VICVectAddr=0;
}

void config_vic_for_timer1(void){
	VICIntSelect=0;
	VICVectCntl0=5|(1<<5);
	VICVectAddr0=(unsigned int)timer1_handler;
	VICIntEnable|=(1<<5);
}

/*  Timer1 interrupt for LCM program  */
void en_timer1_interrupt(void){
	T1PC=0;
	T1MR0=250;
	T1MCR=3;
	T1PR=60000-1;
	T1TC=0;
}
