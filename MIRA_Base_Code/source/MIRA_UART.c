/*
 * MIRA_UART.c
 *
 *  Created on: Mar 17, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_UART.h"


/******************* HWIs ******************/
void UART_ISR(void) {
    int i = 4;
    g_iInByte = 0;
    while (UARTCharsAvail(UART0_BASE)) {
        switch (i) {
        case 4:
            g_iInByte += (UARTCharGetNonBlocking(UART0_BASE) - 0x30) * 1000;
            break;

        case 3:
            g_iInByte += (UARTCharGetNonBlocking(UART0_BASE) - 0x30) * 100;
            break;

        case 2:
            g_iInByte += (UARTCharGetNonBlocking(UART0_BASE) - 0x30) * 10;
            break;

        case 1:
            g_iInByte += (UARTCharGetNonBlocking(UART0_BASE) - 0x30);
            break;

        default:
            UART_Print(g_pcReceivedMsgError, g_ui8ReceivedMsgErrorLen);
            break;
        }
        i--;
    }
    g_iInByte -= 4096;
    UART_Print_Num(g_iInByte);
    UART_Print(g_pcReceivedMsg, g_ui8ReceivedMsgLen);
    UARTIntClear(UART0_BASE, UART_INT_RX);
}


/**************** Clock SWIs ***************/
void UART_Timer(void) {
    Semaphore_post(UART_Semaphore);
}


/****************** Tasks *****************/
void UART_Transmit(void) {
    while(1) {
        Semaphore_pend(UART_Semaphore, BIOS_WAIT_FOREVER);
    }
}


/************* Helper Functions ************/
void UART_Print(char* str, uint8_t len) {
    int i;
    for (i = 0; i < len; i++) {
        UARTCharPut(UART0_BASE,str[i]);
    }
}

void UART_Print_Num(int num) {
    char numArray[5];
    int i;
    if (num < 0) {
        numArray[0] = '-';
        num = -num;
    } else {
        numArray[0] = ' ';
    }
    for (i = 5; i > 1; i--) {
        numArray[i-1] = (num % 10) + 0x30;
        num /= 10;
    }
    UART_Print(numArray, 5);
}


/************* Setup Functions *************/
void UART_Setup(void) {
    // Enable peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Set UART clock
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Configure UART for 115200 baud, 8n1 operation
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_PAR_NONE));

    // Enable transmit and receive FIFOs
    UARTFIFOEnable(UART0_BASE);

    // Set FIFO receive level to 2
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX2_8);

    // Enable UART receive interrupts
    UARTIntEnable(UART0_BASE, UART_INT_RX);

    // Enable UART0
//    UARTEnable(UART0_BASE);

    // Put character in output buffer
    UART_Print(g_pcStartupMsg, g_ui8StartupMsgLen);
}

