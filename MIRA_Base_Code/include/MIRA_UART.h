/*
 * MIRA_UART.h
 *
 *  Created on: Mar 17, 2018
 *   Edited on: Mar 27, 2018
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


/************ Local Header files ***********/
#include "include/MIRA_CAN.h"
#include "include/MIRA_GPIO.h"


/***************** Defines *****************/
#define INIT_DATA_BUFFER_LENGTH 25
#define UPDATE_DATA_BUFFER_LENGTH 7


/*********** Function Prototypes ***********/
// HWIs
void UART_ISR(void);

// SWIs
void UART_Timer(void);

// Tasks
void UART_Init(void);
void UART_Transmit(void);
void UART_Update_Joints(void);

// Helper Functions
void UART_Print(char* str, uint8_t len);
void UART_Print_Num(int num);

// Setup Functions
void UART_Setup(void);


/************* Global Variables ************/
volatile uint32_t UART_State;

uint8_t Init_Data[INIT_DATA_BUFFER_LENGTH];
volatile uint8_t Global_Init_Data[INIT_DATA_BUFFER_LENGTH];
uint32_t Init_Data_Index;

uint8_t Update_Data[UPDATE_DATA_BUFFER_LENGTH];
volatile uint8_t Global_Update_Data[UPDATE_DATA_BUFFER_LENGTH];
uint32_t Update_Data_Index;

uint32_t Init_Joint_Number; // Joint index for initialization
uint32_t Joint_Index;       // Joint index for updates


// Strings for printing
static char* Startup_Message = "Initialized!";
static uint8_t Startup_Message_Length = 12;
static char* Received_Message = "Message received!\n\r";
static uint8_t Received_Message_Length = 20;
static char* Receive_Error_Message = "Error receiving message\n\r";
static uint8_t Receive_Error_Message_Length = 26;
static char* Ack_Pointer = "Y";
static uint8_t Ack_Pointer_Length = 1;


#endif /* INCLUDE_MIRA_UART_H_ */
