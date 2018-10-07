/*
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
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
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
#include<stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define yellow LATEbits.LATE0
#define red LATEbits.LATE1
#define white LATEbits.LATE2
#define usr PORTEbits.RE6
#define prog PORTEbits.RE7


void delay(void);

typedef enum {YELLOW, RED, WHITE} States;

int main(void){
    
    TRISE = 0;
    TRISEbits.TRISE6 = 1;
    TRISEbits.TRISE7 = 1;
    
    yellow = 1;
    red = 1;
    white = 1;
    
    States st = YELLOW;
    
    while(1){
        switch(st){
            case YELLOW:
                yellow = 0;
                red = 1;
                white = 1; break;
            case RED:
                yellow = 1;
                red = 0;
                white = 1; break;
            case WHITE:
                yellow = 1;
                red = 1;
                white = 0; break;         
            }
        
        
        if(usr == 0){
            switch(st){
                case YELLOW:
                    st = RED;
                    break;
                case RED:
                    st = WHITE;
                    break;
                case WHITE:
                    st = YELLOW;
                    break;
            }
            delay();
        }
        if(prog ==0){
            switch(st){
                case YELLOW:
                    st = WHITE;
                    break;
                case RED:
                    st = YELLOW;
                    break;
                case WHITE:
                    st = RED;
                    break;
            }
            delay();
        }
        
        
        
    }
    
    
}

void delay(void){
    int j;
    for(j=0; j<= (1000000/3); j++);
}
*/