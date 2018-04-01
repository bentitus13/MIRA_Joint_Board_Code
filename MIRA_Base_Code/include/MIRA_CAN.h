/*
 * MIRA_CAN.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 27, 2018
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


/************ Local Header files ***********/
#include "include/MIRA_GPIO.h"


/***************** Defines *****************/
// Receive message IDs (just lower 5 bits)IDs
#define RX_JOINT1_ID        0x001
#define RX_JOINT2_ID        0x002
#define RX_JOINT3_ID        0x003
#define RX_JOINT4_ID        0x004
#define RX_JOINT5_ID        0x005
#define RX_JOINT6_ID        0x006

// Transmit message IDs
#define TX_JOINT1_ID        0x021
#define TX_JOINT2_ID        0x022
#define TX_JOINT3_ID        0x023
#define TX_JOINT4_ID        0x024
#define TX_JOINT5_ID        0x025
#define TX_JOINT6_ID        0x026

// Receive message object numbers
#define RX_JOINT1           1
#define RX_JOINT2           2
#define RX_JOINT3           3
#define RX_JOINT4           4
#define RX_JOINT5           5
#define RX_JOINT6           6

// Transmit message object numbers
#define TX_JOINT1           21
#define TX_JOINT2           22
#define TX_JOINT3           23
#define TX_JOINT4           24
#define TX_JOINT5           25
#define TX_JOINT6           26


/*********** Function Prototypes ***********/
// HWIs
void CAN_ISR(void);

// SWIs
void CAN_Timer(void);

// Tasks
void CAN_Send(void);

// Helper Functions
void CAN_Error_Handler(void);
void Setup_TX_Joint1(void);
void Setup_TX_Joint2(void);
void Setup_TX_Joint3(void);
void Setup_TX_Joint4(void);
void Setup_TX_Joint5(void);
void Setup_TX_Joint6(void);
void Setup_RX_Joint1(void);
void Setup_RX_Joint2(void);
void Setup_RX_Joint3(void);
void Setup_RX_Joint4(void);
void Setup_RX_Joint5(void);
void Setup_RX_Joint6(void);

// Setup Functions
void CAN_Setup(void);


/**************** Structs ******************/
typedef struct Joint_Struct {
    // CAN Object numbers
    uint32_t TX_Object_Number;
    uint32_t RX_Object_Number;

    // Joint board ID, raw number (0-63)
    uint16_t Joint_Board_ID;

    // Message ID, bit-shifted joint board ID
    uint16_t Message_ID;

    // Data variables
    uint16_t TX_Data[2];
    uint16_t RX_Data[2];
    float TX_Init_PIDP_Data;
    float TX_Init_PIDI_Data;
    float TX_Init_PIDD_Data;
    uint16_t TX_Init_Encoder_Data;

    // CAN transmit message objects
    tCANMsgObject CAN_TX_Joint;

    // CAN receive message objects
    tCANMsgObject CAN_RX_Joint;
} Joint;


/************* Global Variables ************/
// Joint number
enum Joint_Number{JOINT1, JOINT2, JOINT3, JOINT4, JOINT5, JOINT6};

// Joints
volatile Joint Joints[6];

// Message count variables
static volatile uint32_t TX0_Message_Count = 0;
static volatile uint32_t RX0_Mesage_Count = 0;

// Global error flags
static volatile uint32_t CAN_Error_Flag = 0;

// Global receive flag
static volatile bool RX0_Flag = 0;

// Global initialized flag
static bool Init_Flag = 0;


#endif /* INCLUDE_MIRA_CAN_H_ */
