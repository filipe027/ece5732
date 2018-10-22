/*#include <xc.h> // constants, funcs for startup and UART
#include <stdlib.h>
#include <stdio.h>

#include "uart1.h"
// Demonstrates spi by using two spi peripherals on the same PIC32,
// one is the master, the other is the slave
// SPI4 will be the master, SPI2 the slave.
// connect
// SDO4 -> SDI3 (pin F5 -> pin D2)
// SDI4 -> SDO3 (pin F4 -> pin D3)
// SCK4 -> SCK3 (pin B14 -> pin D1)
int main(void) {
    setUart();
    TRISEbits.TRISE6 = 1;
    char buf[100];
    
    // setup NU32 LED?s and buttons
    //NU32_Startup();
    // Master - SPI4, pins are: SDI4(F4), SDO4(F5), SCK4(B14), SS4(B8); not connected)
    // since the pic is just starting, we know that SPI is off. We rely on defaults here
    SPI4BUF; // clear the rx buffer by reading from it
    SPI4BRG = 0x4; // baud rate to 8 MHz [SPI4BRG = (80000000/(2*desired))-1]
    SPI4STATbits.SPIROV = 0; // clear the overflow bit
    SPI4CONbits.MODE32 = 0; // use 16 bit mode
    SPI4CONbits.MODE16 = 1;
    SPI4CONbits.MSTEN = 1; // master operation
    SPI4CONbits.ON = 1; // turn on spi 4
    // Slave - SPI2, pins are: SDI3(D2), SDO3(D3), SCK3(D1), SS3(D9; not connected)
    SPI2BUF; // clear the rx buffer
    SPI2STATbits.SPIROV = 0; // clear the overflow
    SPI2CONbits.MODE32 = 0; // use 16 bit mode
    SPI2CONbits.MODE16 = 1;
    SPI2CONbits.MSTEN = 0; // slave mode
    SPI2CONbits.ON = 1; // turn spi on. Note: in slave mode you do not set baud
    while(PORTEbits.RE6 == 1);
    delay(100000);
    uart_sendCharArr("**Start**\n");
    while(1) {
        
        unsigned short master = 0xAAAA, slave = 0xBBBB;
        unsigned short rmaster = 0, rslave = 0;
        //NU32_WriteUART3("Enter two 16-bit hex words (lowercase) to send from ");
        //NU32_WriteUART3("master and slave (i.e., 0xd13f 0xb075): \r\n");
          
        if(PORTEbits.RE6 == 0){
            master = 0xCCCC;
            slave = 0xDDDD;
        }
        
        // have the slave write its data to its SPI buffer
        // (note, the data will not be sent until the master performs a write)
        SPI2BUF = slave;
        // now the master performs a write
        SPI4BUF = master;
        // wait until the master receives the data
        while(!SPI4STATbits.SPIRBF) {
            ; // could check SPI2STAT instead; slave receives data same time as master
        }
        // receive the data
        rmaster = SPI4BUF;
        rslave = SPI2BUF;
        sprintf(buf,"Master sent 0x%04x, Slave sent 0x%04x\r\n", master, slave);
        //NU32_WriteUART3(buf);
        uart_sendCharArr(buf);
        sprintf(buf," Slave read 0x%04x, Master read 0x%04x\r\n",rslave,rmaster);
        //NU32_WriteUART3(buf);
        uart_sendCharArr(buf);
        delay(500000);
    }
    return 0;
    
}
*/