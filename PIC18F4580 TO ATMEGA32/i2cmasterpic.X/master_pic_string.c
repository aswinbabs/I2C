/*
 * File:   master_pic_string.c
 * Author: ASWATHY BABU
 *
 * Created on 25 October, 2024, 9:47 AM
 */


#include<pic18.h>
void I2C_INIT();
void _I2C_STOP();
void I2C_SEND_DATA(char a);
char I2C_READ_DATA(char a);
void I2C_SEND_STRING(const char *str);
void _I2C_START();
void main()
{
TRISB=TRISD=0x00;  //set as outputs
TRISC=0x18;        //RC3 & RC4 as inputs
for(long i=0;i<100000;i++);//delay

I2C_INIT();
_I2C_START();//start slave ad+R/w  
for(long i=0;i<100000;i++);//delay

I2C_SEND_DATA(0xD0);//1101 0000
I2C_SEND_STRING("HERE WE GO");
_I2C_STOP(); 
while(1);

}

void I2C_INIT()
{
SSPSTAT=0x00;//0000
SSPCON1=0x28;//SSPEN & SSPM3= 1, enable serial port , set to master mode
SSPCON2=0x00;//0000
SSPADD=49;//calculated for F_I2C speed = 1KHz and PIC clock speed = 20MHz   

// (Formula),    SSPADD = (F_OSC/(4*F_I2C)) - 1

} 
void _I2C_START()
{
SEN=1; //from SSPCON2 register SEN = 1, start condition enabled and cleared automatically by hardware
while(SEN==1);//until condition true
}

void _I2C_STOP()
{
PEN=1; //from register SSPCON2 , PEN = 1, stop condition enabled and cleared automatically by hardware
while(PEN==1);// until condition true
}
void I2C_SEND_DATA(char a)
{
SSPIF=0;
SSPBUF=a;
while(SSPIF==0);
}
void I2C_SEND_STRING(const char *str)
{
    while(*str != '\0')
    {
        int i;
        I2C_SEND_DATA(*str);
        str++;
        for(i=0;i<1000;i++);
    }
    I2C_SEND_DATA('\0');
}

char I2C_READ_DATA(char a)
{
RCEN=1;//from SSPCON2 ,RCEN = 1 , Enable receive mode for I2C
while(RCEN);//until true
ACKDT=a;//1- NACK before stopping 0->ack
ACKEN=1;
while(ACKEN);
return SSPBUF;
}



