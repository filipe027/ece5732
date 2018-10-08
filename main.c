
// PIC32MX795F512L Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (RMII Enabled)
#pragma config FETHIO = OFF             // Ethernet I/O Pin Select (Alternate Ethernet I/O)
#pragma config FCANIO = OFF             // CAN I/O Pin Select (Alternate CAN I/O)
#pragma config FUSBIDIO = OFF           // USB USID Selection (Controlled by Port Function)
#pragma config FVBUSONIO = OFF          // USB VBUS ON Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_18         // PLL Multiplier (18x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)


// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = ON                 // Boot Flash Write Protect bit (Protection Enabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


#define yellow LATEbits.LATE0
#define red LATEbits.LATE1
#define white LATEbits.LATE2
#define green LATEbits.LATE3
#define usr PORTEbits.RE6
#define prog PORTEbits.RE7

char uart_readChar(void);
void uart_sendChar(char c);
char* toArray(int number);
void uart_sendIntCharArray(int number);
void uart_sendCharArr(char arr[]);

void delay(int);
uint32_t count8(uint32_t* x);

void setUart(){
    U1MODEbits.BRGH = 0;        //baud rate 9600
    U1BRG = 520;
    
    U1MODEbits.SIDL = 0;
    U1MODEbits.IREN = 0;
    U1MODEbits.RTSMD = 0;
    U1MODEbits.UEN = 0b00;        
    U1MODEbits.WAKE = 1;
    U1MODEbits.LPBACK = 0;
    U1MODEbits.RXINV = 0;
    U1MODEbits.PDSEL = 0b00;        
    U1MODEbits.STSEL = 0;
    
    U1MODEbits.ON = 1;
    
    U1STAbits.UTXINV = 0;
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
}

    /*int main(void){
        uint32_t ct = 0;

        TRISE = 0;

        TRISEbits.TRISE6 = 1;
        TRISEbits.TRISE7 = 1;

        yellow = 1;
        red = 1;
        white = 1;
        green = 1;


        while(1){
            LATE = count8(&ct);
            delay();
        }

     }*/
int main(void){
    setUart();
    
    int ADCValue = 0;
    TRISE = 0;
    
    AD1PCFG = 0xFFFB;
    AD1CON1 = 0;
    AD1CHS = 0x00020000;
    AD1CSSL=0;
    AD1CON3 = 0x0002;
    AD1CON2 = 0;
    AD1CON1SET = 0x8000;
    red = 0;
    while(1)
    {
        AD1CON1SET = 0x0002;
        delay(100000);
        white = 0;
        AD1CON1CLR = 0x0002;
        while(!(AD1CON1 & 0x0001));
        green = 0;
        ADCValue = ADC1BUF0;
        
        if(ADCValue >500){
            yellow = 0;
            red = 1;
            white = 1;
            green = 1;
            //uart_sendChar('1');
        }
        else{
            yellow = 1;
            red = 0;
            white = 1;
            green = 1;
            //uart_sendChar('0');
        }
        uart_sendIntCharArray(ADCValue);
        delay(1000000);
    }
    
    
}





uint32_t count8(uint32_t* x){
    if(*x >= 15 || *x <0){
        *x = 0;
    }
    
    else{
        (*x)++;
    }
    return (~(*x) & 0x000F);
}

void uart_sendIntCharArray(int number)
{
    // Figures out how many digits there are in a integer number.
    // OBS: log10 not working
    int n = 1;    
    while((number % (int)pow(10,n)) !=  number) 
        n++;
    
    int i;
    
    char numArr[n+1];
    numArr[n] = '\0';
    for ( i = 0; i < n; ++i, number /= 10 ) // Divides the number by 10
    {
        numArr[(n-1) - i] = (number % 10) + '0'; // %10 gives the last digit
        // +'0' transforms a int number into a char number
    }
    
    uart_sendCharArr(numArr);// send char number array
    
    
}