/*
 * MIRA_Encoder.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_ENCODER_H_
#define INCLUDE_MIRA_ENCODER_H_


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
#define READ_ANGLE        0x3FFF         // Data to send over SSI to read angle from AS5055
#define ENCODER_WRAP(val) (0x0FFF & val) // Wrap encoder value to 0-4096


/*********** Function Prototypes ***********/
// HWIs
void SSI_ISR(void);

// SWIs
void SSI_Timer(void);

// Tasks
void SSI_Transmit(void);

// Helper Functions
void SSI_Send(uint16_t num);

// Setup Functions
void SSI_Setup(void);


/************* Global Variables ************/
// Joint angle read in by encoder
volatile int Encoder_Value;

// Offset for tuning the encoder
int Encoder_Offset;

// Actual joint angle
float Joint_Angle;


#endif /* INCLUDE_MIRA_ENCODER_H_ */
