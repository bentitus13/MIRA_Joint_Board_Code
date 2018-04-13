/*
 * MIRA_GPIO.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 26, 2018
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
// Switches
#define SW1_PORT           GPIO_PORTA_BASE  // Pin A7
#define SW2_PORT           GPIO_PORTA_BASE  // Pin A6
#define SW3_PORT           GPIO_PORTD_BASE  // Pin D1
#define SW4_PORT           GPIO_PORTB_BASE  // Pin B4
#define SW5_PORT           GPIO_PORTD_BASE  // Pin D2
#define SW6_PORT           GPIO_PORTD_BASE  // Pin D3

#define SW1_PIN            GPIO_PIN_7       // Pin A7
#define SW2_PIN            GPIO_PIN_6       // Pin A6
#define SW3_PIN            GPIO_PIN_1       // Pin D1
#define SW4_PIN            GPIO_PIN_4       // Pin B4
#define SW5_PIN            GPIO_PIN_2       // Pin D2
#define SW6_PIN            GPIO_PIN_3       // Pin D3

// SPI pins
#define SPI_PORT           GPIO_PORTA_BASE  // Pin A2-A5

#define SCLK_PIN           GPIO_PIN_2       // Pin A2
#define CS_PIN             GPIO_PIN_3       // Pin A3
#define MISO_PIN           GPIO_PIN_4       // Pin A4
#define MOSI_PIN           GPIO_PIN_5       // Pin A5

#define SCLK_CONFIG        GPIO_PA2_SSI0CLK // Pin A2
#define CS_CONFIG          GPIO_PA3_SSI0FSS // Pin A3
#define MISO_CONFIG        GPIO_PA4_SSI0RX  // Pin A3
#define MOSI_CONFIG        GPIO_PA5_SSI0TX  // Pin A5

// Motor pins
#define MOTOR_PWM_PORT     GPIO_PORTB_BASE  // Pin B6
#define MOTOR_DIR_PORT     GPIO_PORTB_BASE  // Pin B7

#define MOTOR_PWM_PIN      GPIO_PIN_6       // Pin B6
#define MOTOR_DIR_PIN      GPIO_PIN_2       // Pin B2

#define MOTOR_PWM_CONFIG   GPIO_PB6_M0PWM0  // Pin B6

// Current Sensor
#define ISEN_PORT          GPIO_PORTE_BASE  // Pin E0

#define ISEN_PIN           GPIO_PIN_0       // Pin E0

// Load Cell pins
#define LOAD_CELL_PORT     GPIO_PORTE_BASE  // Pin E2

#define LOAD_CELL_PIN      GPIO_PIN_2       // Pin E2

// CAN pins
#define CAN_PORT           GPIO_PORTE_BASE  // Pin E4, E5

#define CANRX_PIN          GPIO_PIN_4       // Pin E4
#define CANTX_PIN          GPIO_PIN_5       // Pin E5

#define CANRX_CONFIG       GPIO_PE4_CAN0RX  // Pin E4
#define CANTX_CONFIG       GPIO_PE5_CAN0TX  // Pin E5

// Heartbeat
#define HEARTBEAT_PORT     GPIO_PORTF_BASE  // Pin F2
#define HEARTBEAT1_PORT     GPIO_PORTB_BASE  // Pin B5

#define HEARTBEAT_PIN      GPIO_PIN_2       // Pin F2
#define HEARTBEAT1_PIN      GPIO_PIN_5       // Pin B5


/*********** Function Prototypes ***********/
// HWIs

// SWIs

// Tasks

// Helper Functions

// Setup Functions
void Pin_Setup(void);


/************* Global Variables ************/


#endif /* INCLUDE_MIRA_GPIO_H_ */
