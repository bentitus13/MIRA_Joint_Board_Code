/*
 * MIRA_GPIO.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
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
// Pins
#define SCLK_PIN       GPIO_PIN_2 // Pin A2
#define CS_PIN         GPIO_PIN_3 // Pin A3
#define MISO_PIN       GPIO_PIN_4 // Pin A4
#define MOSI_PIN       GPIO_PIN_5 // Pin A5
#define SW2_PIN        GPIO_PIN_6 // Pin A6
#define SW1_PIN        GPIO_PIN_7 // Pin A7
#define SW4_PIN        GPIO_PIN_4 // Pin B4
#define MOTOR_DIR_PIN  GPIO_PIN_5 // Pin B5
#define MOTOR_PWM_PIN  GPIO_PIN_6 // Pin B6
#define SW3_PIN        GPIO_PIN_1 // Pin D1
#define SW5_PIN        GPIO_PIN_2 // Pin D2
#define SW6_PIN        GPIO_PIN_3 // Pin D3
#define ISEN_PIN       GPIO_PIN_0 // Pin E0
#define LOAD_CELL_PIN  GPIO_PIN_2 // Pin E2
#define CAN0RX_PIN     GPIO_PIN_4 // Pin E4
#define CAN0TX_PIN     GPIO_PIN_5 // Pin E5
#define HEARTBEAT_PIN  GPIO_PIN_2 // Pin F2


/*********** Function Prototypes ***********/
// HWIs

// SWIs

// Tasks

// Helper Functions

// Setup Functions
void Pin_Setup(void);


/************* Global Variables ************/


#endif /* INCLUDE_MIRA_GPIO_H_ */
