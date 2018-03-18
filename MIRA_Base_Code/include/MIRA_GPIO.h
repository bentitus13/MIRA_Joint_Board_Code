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
#include <xdc/std.h>
#include <xdc/cfg/global.h>


/************ BIOS Header files ************/
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


/*********** TI RTOS Header files **********/
#include <inc/hw_gpio.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <ti/drivers/GPIO.h>
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>


/************ Local Header files ***********/
#include "include/Board.h"
#include "include/MIRA_CAN.h"
#include "include/MIRA_Current_Sensor.h"
#include "include/MIRA_Encoder.h"
#include "include/MIRA_GPIO.h"
#include "include/MIRA_Load_Cell.h"
#include "include/MIRA_Motor_Control.h"


/***************** Defines *****************/
// Pins
#define SCLK_PIN       GPIO_PIN_2 // Pin A2
#define CS_PIN         GPIO_PIN_3 // Pin A3
#define MISO_PIN       GPIO_PIN_4 // Pin A4
#define MOSI_PIN       GPIO_PIN_5 // Pin A5
#define MOTOR_DIR_PIN  GPIO_PIN_5 // Pin B5
#define MOTOR_PWM_PIN  GPIO_PIN_6 // Pin B6
#define ISEN_PIN       GPIO_PIN_0 // Pin E0
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
