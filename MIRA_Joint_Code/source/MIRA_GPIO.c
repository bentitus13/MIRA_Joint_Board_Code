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


    // Pf2 is Heartbeat LED (Blue)
    GPIOPinTypeGPIOOutput(HEARTBEAT_PORT, HEARTBEAT_PIN);


    // PB5 is boosterpack heartbeat
    GPIOPinTypeGPIOOutput(HEARTBEAT1_PORT, HEARTBEAT1_PIN);


    // Initialize motor PWM output
    GPIOPinConfigure(MOTOR_PWM_CONFIG);
    GPIOPinTypePWM(MOTOR_PWM_PORT, MOTOR_PWM_PIN);


    // Initialize motor direction
    GPIOPinTypeGPIOOutput(MOTOR_DIR_PORT, MOTOR_DIR_PIN);


    // Initialize SSI
    GPIOPinConfigure(SCLK_CONFIG);      // PA2 -> SCLK
    GPIOPinConfigure(CS_CONFIG);        // PA3 -> CS
    GPIOPinConfigure(MISO_CONFIG);      // PA4 -> MISO
    GPIOPinConfigure(MOSI_CONFIG);      // PA5 -> MOSI
    GPIOPinTypeSSI(SPI_PORT, SCLK_PIN | CS_PIN | MISO_PIN | MOSI_PIN);


    // Initialize CAN0RX and CAN0TX
    GPIOPinConfigure(CANRX_CONFIG);
    GPIOPinConfigure(CANTX_CONFIG);
    GPIOPinTypeCAN(CAN_PORT, GPIO_PIN_4 | GPIO_PIN_5);


    // Initialize current sensor input
    GPIOPinTypeADC(ISEN_PORT, ISEN_PIN);


    // Initialize load cell input
    GPIOPinTypeADC(LOAD_CELL_PORT, LOAD_CELL_PIN);


    // Initialize SW1 as GPIO input
    GPIOPinTypeGPIOInput(SW1_PORT, SW1_PIN);
    GPIOPadConfigSet(SW1_PORT, SW1_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


    // Initialize SW2 as GPIO input
    GPIOPinTypeGPIOInput(SW2_PORT, SW2_PIN);
    GPIOPadConfigSet(SW2_PORT, SW2_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


    // Initialize SW3 as GPIO input
    GPIOPinTypeGPIOInput(SW3_PORT, SW3_PIN);
    GPIOPadConfigSet(SW3_PORT, SW3_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


    // Initialize SW4 as GPIO input
    GPIOPinTypeGPIOInput(SW4_PORT, SW4_PIN);
    GPIOPadConfigSet(SW4_PORT, SW4_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


    // Initialize SW5 as GPIO input
    GPIOPinTypeGPIOInput(SW5_PORT, SW5_PIN);
    GPIOPadConfigSet(SW5_PORT, SW5_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


    // Initialize SW6 as GPIO input
    GPIOPinTypeGPIOInput(SW6_PORT, SW6_PIN);
    GPIOPadConfigSet(SW6_PORT, SW6_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
}
