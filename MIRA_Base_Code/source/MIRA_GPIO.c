/*
 * MIRA_GPIO.c
 *
 *  Created on: Mar 17, 2018
 *   Edited on: Mar 26, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_GPIO.h"


/******************* HWIs ******************/


/**************** Clock SWIs ***************/


/****************** Tasks *****************/


/************* Helper Functions ************/


/************* Setup Functions *************/
void Pin_Setup(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Set GPIO A0 and A1 as UART pins.
    GPIOPinConfigure(UARTRX_CONFIG);
    GPIOPinConfigure(UARTTX_CONFIG);
    GPIOPinTypeUART(UART_PORT, UARTRX_PIN | UARTTX_PIN);


    // Pf2 is Heartbeat LED (Blue)
    GPIOPinTypeGPIOOutput(HEARTBEAT_PORT, HEARTBEAT_RED_PIN | HEARTBEAT_BLUE_PIN);


    // Initialize CAN0RX and CAN0TX
    GPIOPinConfigure(CANRX_CONFIG);
    GPIOPinConfigure(CANTX_CONFIG);
    GPIOPinTypeCAN(CAN_PORT, CANRX_PIN | CANTX_PIN);
}
