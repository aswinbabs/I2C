/*
 * File:   slave_atmega_string_hw.c
 * Author: ASWATHY BABU
 *
 * Created on 29 October, 2024, 11:05 PM
 */


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void I2C_INIT();
char I2C_READ_DATA();
void DISPLAY(const char *a);
void data(char a);
void command(char a);
void LCD_INIT();
int main(void)
{
	DDRA=DDRD=DDRB = 0XFF; //out to lcd 
     
    
    DDRC = 0xFC; //except i2c portc is output
	
    
    char buffer[16];    // Buffer to store received string
    char *p = buffer;
    
    LCD_INIT();
    I2C_INIT();
    
	while(1)
    {	
     char string = I2C_READ_DATA();
     if (string == '\0')  // End of string
        {
            *p = '\0';              // Null-terminate the buffer
            DISPLAY(buffer);         // Display entire buffer
            p = buffer;              // Reset buffer pointer
        }
        else
        {
            *p++ = string;    // Store received char and move pointer
        }
    }
    
}
void LCD_INIT()
{
  command(0X01);
  command(0X38);
  command(0X06);
  command(0X0E);
  command(0X80);
}
void command(char a){
    PORTD=0X40; //  enable
    PORTB=a;
    _delay_ms(1);
    PORTD=0X00;      //
}
void data(char a)
{
 PORTD=0X50;      //  enable, register select
 PORTB=a;
 _delay_ms(1);
 PORTD=0X10;      //
    
}
void DISPLAY(const char *a)
{
    while(*a!='\0'){
        data(*a);
        a++;
    }
}

void I2C_INIT()
{
	DDRC=0xC0;   //sets SDA,SCL as input and pc6 ,pc7 output
    TWBR = 32;   // Set I2C clock to 100 kHz for an 8 MHz system clock
	TWAR=0xD0;   //  SLAVE ADDRESS 
	TWCR=0x44;   //     0100 0100  ,(TWEA) Enable acknowledgment bit , it is set in receiver mode   , then (TWEN) enable SCL and SDL as serial port
	TWCR|=0x80;  // TWCR=TWCR|0x80    , TWINT (interrupt flag) sets - meaning global interrupt activated , it will be cleared automatically after completion 
	while((TWCR&(0x80))==0);//slave , until current task completes

}

char I2C_READ_DATA()
{
	TWCR=0x44;  // TWCR=0x44;  Clear TWI interrupt flag ie by acknowledging , then Enable TWI  
	TWCR|=0x80; // Enable TWINT
	while (!(TWCR & (1<<TWINT))); //while((TWCR&(0x80))==0); slave ad+W
	return TWDR;  //these 8 bit contains data byte 

}
