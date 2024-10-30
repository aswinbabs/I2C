/*
 * File:   slave_atmega.c
 * Author: ASWATHY BABU
 *
 * Created on 21 October, 2024, 2:14 PM
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void I2C_INIT();
char I2C_READ_DATA();
void UART_INIT();
void UART_TRANSMIT(char b);
int main(void)
{
	DDRA=DDRB=0xff;
	DDRD=0X02;
	UART_INIT();
	I2C_INIT();
	char v=I2C_READ_DATA();
	UART_TRANSMIT(v);
	char w=I2C_READ_DATA();
	UART_TRANSMIT(w);
    
	while(1);
}

void UART_INIT()
{
	UCSRA=0X00; //0000 0000
	UCSRB=0X18; // Enable RX and TX
	UCSRC=0X86; // URSEL (bit 7) must be high for reading , UCSZ1 & UCSZ0 high (means 8 bit data)
	UBRRL=0X33; // for baud rate 9600 bits/seconds , UBRR = 51 (from frequency 8MHz) , so the binary value of 51 is  0011 0011 ie 0x33
	UBRRH=0X00; // 0000 0000
}

void UART_TRANSMIT(char b)
{
	while((UCSRA&0X20)==0); // waits until buffer is empty
	UCSRA=0X20;             // clears buffer
    	UDR=b;	            // writes data into UDR
}  

void I2C_INIT()
{
	DDRC=0;   //sets the port c as input
	TWAR=0xF0;//  SLAVE ADDRESS 
	TWCR=0x44;//     0100 0100  ,(TWEA) Enable acknowledgment bit , it is set in receiver mode   , then (TWEN) enable SCL and SDL as serial port
	TWCR|=0x80;// TWCR=TWCR|0x80    , TWINT (interrupt flag) sets - meaning global interrupt activated , it will be cleared automatically after completion 
	while((TWCR&(0x80))==0);//slave , until current task completes

}

char I2C_READ_DATA()
{
	TWCR=0x44;  // TWCR=0x44;  Clear TWI interrupt flag ie by acknowledging , then Enable TWI  
	TWCR|=0x80; // Enable TWINT
	while (!(TWCR & (1<<TWINT))); //while((TWCR&(0x80))==0); slave ad+W
	return TWDR;  //these 8 bit contains data byte 

}
