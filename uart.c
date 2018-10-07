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