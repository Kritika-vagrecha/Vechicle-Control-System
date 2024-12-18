/*  UART0 DRIVER  */
#include<lpc21xx.h>
#include"header.h"

void uart0_init(unsigned int baud){
	unsigned int result=0;
	int a[]={15,60,30,15,15};

	unsigned int pclk=0;

	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);

	PINSEL0|=5;

	U0LCR=0X83;
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xFF;
	U0LCR^=(1<<7);
	//	U0LCR=0X03;
}

#define THRE ((U0LSR>>5)&1)

void uart0_tx(unsigned char data){
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(char *ptr){
	while(*ptr){
//		uart0_tx(*ptr);
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}				
}

#define RDR (U0LSR&1)

unsigned char uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}

void uart0_ascii(unsigned char data){
	uart0_tx((data/100)+48);
	uart0_tx(((data/10)%10)+48);
	uart0_tx((data%10)+48);
}

void uart0_ascii_hex(unsigned char data){
	unsigned char t;
	
	uart0_tx_string("0x");
	t=(data&0xf0)>>4;
	uart0_tx(t+48);
	
	t=data&0xf;
	if(t>9)
		uart0_tx('A'+(t-10));
	else
		uart0_tx('0'+t);
}

void uart0_rx_string(char *ptr,int len){
	unsigned char i;
	for(i=0;i<len;i++){
		while(RDR==0);
		ptr[i]=U0RBR;
		if(ptr[i]=='\r')
			break;
	}
	ptr[i]='\0';
}

void uart0_float(float num){
	int temp,temp1,i,l;
	char a[16];
	if(num==0){
		//uart0_tx_string("0.000000");
		uart0_tx_string("0.00");		// for calculator
		return;
	}
   	
	if(num<0){
		uart0_tx('-');
		num=-num;
	}

	temp=num;
	if(temp==0){
		uart0_tx('0');
	}
	else{
		for(l=0,temp1=temp;temp1;temp1=temp1/10,l++);
		l--;
	
		for(temp1=temp,i=0;temp1;temp1=temp1/10,i++){
			a[i]=(temp1%10)+48;
		}
	
		//for(i=l;i>=0;i--){
		for(i=l;i>=0;i--){
			uart0_tx(a[i]);
		}
	}
		
	uart0_tx('.');
	
	temp=(num-temp)*1000000;
	if(temp==0){
		//uart0_tx_string("000000");
		uart0_tx_string("00");		// for calculator
	}
	else{
		for(i=0;temp;temp=temp/10,i++){
			a[i]=(temp%10)+48;
		}
		for(i=1;i>=0;i--){
			uart0_tx(a[i]);
		}
	}
}
void uart0_integer(int num){
	int temp,l,i=0;
	char a[16];
	if(num==0){
		uart0_tx('0');
		return;
	}
   	
	if(num<0){
		uart0_tx('-');
		num=-num;
	}

	for(temp=num,l=0;temp;temp=temp/10,l++);
	l--;

	for(temp=num;temp;temp=temp/10,i++){
		a[i]=(temp%10)+48;
	}

	for(i=l;i>=0;i--){
		uart0_tx(a[i]);
	}
}

void uart0_time(unsigned char s,unsigned char m,unsigned char h,char *p){
	*p++=(((h&0x1f)/0x10)+48);
	*p++=((h%0x10)+48);
	
	*p++=(':');
	
	*p++=((m/0x10)+48);
	*p++=((m%0x10)+48);
	
	*p++=(':');
	
	*p++=((s/0x10)+48);
	*p++=((s%0x10)+48);

//	if((h>>6)&1){
//		if((h>>5)&1)
//			*p++=("PM");
//		else
//			*p++=("AM");
//	}		
}		 
void uart0_date(unsigned char dd,unsigned char mm,unsigned char yy,char *p){
	*p++=((dd/0x10)+48);
	*p++=((dd%0x10)+48);
	
	*p++=('/');
	
	*p++=((mm/0x10)+48);
	*p++=((mm%0x10)+48);
	
	*p++=('/');
	
	*p++=('2');
	*p++=('0');
	*p++=((yy/0x10)+48);
	*p++=((yy%0x10)+48);
}
void uart0_int_hex(unsigned int n){
	int i,f=1,l;
	unsigned char t;
	for(i=0;i<8;i++){
		l=4*(7-i);
		t=(n>>l)&0xf;
		if(f)
			if(t)
				f=0;
		if(f==0){
			if(t>9)
				uart0_tx('A'+(t-10));
			else
				uart0_tx(t+48);
		}
	}
}
