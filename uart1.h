/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _UART1_H    /* Guard against multiple inclusion */
#define _UART1_H

void uart_sendCharArr(char arr[]);
char uart_readChar(void);
uart_sendChar(char c);
void setUart();

#endif _UART1_H

/* *****************************************************************************
 End of File
 */
