/*
 * MIRA_CAN.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_CAN_H_
#define INCLUDE_MIRA_CAN_H_

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
#include <inc/hw_can.h>
#include <inc/hw_gpio.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <ti/drivers/GPIO.h>
#include "driverlib/adc.h"
#include "driverlib/can.h"
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
#define CANTX0ID                2  // Set TXID to 2
#define CANRX0ID                0  // Set RXID to 0 to receive all messages

#define TX0OBJECT                2 // Set TXOBJECT to channel 2
#define RX0OBJECT                1 // Set RX0OBJECT to channel 1


/*********** Function Prototypes ***********/
// HWIs
void CAN_ISR(void);

// SWIs
void CAN_Timer(void);

// Tasks
void CAN_Task(void);

// Helper Functions
void CAN_Error_Handler(void);

// Setup Functions
void CAN_Setup(void);


/************* Global Variables ************/
// Message count variables
volatile uint32_t TX0_Message_Count = 0;
volatile uint32_t RX0_Mesage_Count = 0;

// Global error flags
volatile uint32_t CAN_Error_Flag = 0;

// Global receive flag
volatile bool RX0_Flag = 0;

// Data variables
uint16_t TX0_Data[2];
uint16_t RX0_Data[2];

// CAN message objects
tCANMsgObject CAN_TX0_Message;
tCANMsgObject CAN_RX0_Message;


#endif /* INCLUDE_MIRA_CAN_H_ */
