#include"header.h"

void uart0_init(u32 baud)
{
	u32 a[]={15,60,30,15,15};
	u32 pclk=a[VPBDIV]*1000000;
	u32 result=0;
	result=pclk/(16*baud);
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=result&0xFF;       //lower byte 
 	U0DLM=(result>>8)&0xFF;   //upper byte
	U0LCR=0x03;
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(u8 data)
{
	U0THR=data;
	while(THRE==0);
}

#define RDR ((U0LSR)&1)
char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_string(char *ptr)
{
		while(*ptr)
		{
			U0THR=*ptr;
			while(THRE==0);
			ptr++;
		}
}


