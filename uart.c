#include <xc.h>

#include "HardwareProfile.h"

void uart_sendChar(char c){
    U1STAbits.UTXEN = 1;
    while(U1STAbits.UTXBF);
    U1TXREG = c;
}

char uart_readChar(void){
    while(!U1STAbits.URXDA)
        return U1RXREG;        
}



void uart_sendCharArr(char arr[]){
    int i = 0;
    while(arr[i] != '\0'){
        uart_sendChar(arr[i]);
        i++;
    }
    uart_sendChar('\0');
}

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