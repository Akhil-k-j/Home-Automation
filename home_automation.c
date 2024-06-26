#include"header.h"
#define SW1 ((IOPIN0>>14)&1)
#define SW2 ((IOPIN0>>15)&1)
#define SW3 ((IOPIN0>>16)&1)
#define LED1 (1<<17)
#define BULB (1<<18)
#define FAN (1<<19)
#define RDR ((U0LSR)&1)

void manual_mode(void)
{
        uart0_tx_string("\r\nManual mode\r\n");
        IOCLR0=LED1;
        while(1)
        {
                if(SW1==0)
                {
                        while(SW1==0);
                        IOSET0=LED1;
                        return;
                }
                else if(SW2==0)
                {
                        while(SW2==0);
                        if((IOSET0>>18)&1)
                        {
                                IOCLR0=BULB;
                        }
                        else
                        {
                                IOSET0=BULB;
                        }
                }
                else if(SW3==0)
                {
                        while(SW3==0);
                        if((IOSET0>>19)&1)
                        {
                                IOCLR0=FAN;
                        }
                        else
                        {
                                IOSET0=FAN;
                        }
                }
        }
}

int main()
{
        char temp;
        uart0_init(9600);
        IODIR0=7<<17;
        IOSET0=7<<17;
L1:
        uart0_tx_string("\r\nBluetooth mode\r\n");
        while(1)
        {
                uart0_tx_string("\r\nMenu:\r\n1)BULB ON\r\n2)BULB OFF\r\n3)FAN ON\r\n4)FAN OFF\r\n");
                while(RDR==0 && SW1==1); 
                if(SW1==0)
                {
                        while(SW1==0);
                        manual_mode();
												temp=U0RBR;  //Suppose, the user enter something(multiple charecters) while being in the Manual mode,
											//the last 1 byte data will be avaialable in the buffer (overrunned) which we should not process.
											//If we read that data , RDR become 0 else RDR become 1 and directly go to the else part on the goto statement, And process it which is against the requirement.
											//since we don't want to process that data, We will simply read the data, to make the RDR FLAG 0 and prepare to read the fresh data;
									goto L1;
                }
                else
                {
                        temp=U0RBR;
                        switch(temp)
                        {
                                case '1':IOCLR0=BULB;break;
                                case '2':IOSET0=BULB;break;
																case '3':IOCLR0=FAN;break;
                                case '4':IOSET0=FAN;break;
                                default:uart0_tx_string("\r\nWrong option\r\n");
                        }
                }
				}
}

