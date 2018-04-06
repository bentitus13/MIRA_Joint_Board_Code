/*
 * MIRA_GPIO.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 27, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_GPIO_H_
#define INCLUDE_MIRA_GPIO_H_


/********** General C Header files *********/
#include <stdbool.h>
#include <stdint.h>


/********** XDCtools Header files **********/


/************ BIOS Header files ************/


/*********** TI RTOS Header files **********/
#include <inc/hw_memmap.h>
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"


/************ Local Header files ***********/


/***************** Defines *****************/
// UART pins
#define UARTRX_PIN         GPIO_PIN_0       // Pin A0
#define UARTTX_PIN         GPIO_PIN_1       // Pin A1

#define UART_PORT          GPIO_PORTA_BASE  // Pin A0, A1

#define UARTRX_CONFIG      GPIO_PA0_U0RX
#define UARTTX_CONFIG      GPIO_PA1_U0TX

// CAN pins
#define CAN_PORT           GPIO_PORTE_BASE  // Pin E4, E5

#define CANRX_PIN          GPIO_PIN_4       // Pin E4
#define CANTX_PIN          GPIO_PIN_5       // Pin E5

#define CANRX_CONFIG       GPIO_PE4_CAN0RX  // Pin E4
#define CANTX_CONFIG       GPIO_PE5_CAN0TX  // Pin E5

// Heartbeat
#define HEARTBEAT_PORT     GPIO_PORTF_BASE  // Pin F2

#define HEARTBEAT_RED_PIN  GPIO_PIN_1       // Pin F1
#define HEARTBEAT_BLUE_PIN GPIO_PIN_2       // Pin F2



/*********** Function Prototypes ***********/
// HWIs

// SWIs

// Tasks

// Helper Functions

// Setup Functions
void Pin_Setup(void);


/************* Global Variables ************/


#endif /* INCLUDE_MIRA_GPIO_H_ */
