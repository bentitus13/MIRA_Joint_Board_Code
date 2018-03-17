/*
 * MIRA_UART.h
 *
 *  Created on: Mar 17, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_UART_H_
#define INCLUDE_MIRA_UART_H_


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


/*********** Function Prototypes ***********/
// HWIs
void UART_ISR(void);

// SWIs

// Tasks

// Helper Functions
void UART_Print(char* str, uint8_t len);
void UART_Print_Num(int num);

// Setup Functions
void UART_Setup(void);


/************* Global Variables ************/
volatile int g_iInByte;


// Strings for printing
char* g_pcStartupMsg = "Initialized!\n\r";
uint8_t g_ui8StartupMsgLen = 15;
char* g_pcReceivedMsg = "Message received!\n\r";
uint8_t g_ui8ReceivedMsgLen = 20;
char* g_pcReceivedMsgError = "Error receiving message\n\r";
uint8_t g_ui8ReceivedMsgErrorLen = 26;



#endif /* INCLUDE_MIRA_UART_H_ */
