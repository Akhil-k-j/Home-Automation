#include<LPC21xx.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef signed  int s32;
typedef signed short s16;
typedef signed char s8;


void delay_ms(unsigned int);
void delay_s(unsigned int);


void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void lcd_integer(int);
void lcd_float(float);
void lcd_cgram(void);
void lcd_hexa(int);
void r_scroll(void);

void uart0_init(u32 );
char uart0_rx(void);
void uart0_tx(u8);
void uart0_tx_string(char *);
