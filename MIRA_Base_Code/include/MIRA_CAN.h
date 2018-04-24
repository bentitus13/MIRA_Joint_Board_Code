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


/************ Local Header files ***********/
#include "include/MIRA_GPIO.h"
#include "include/MIRA_UART.h"


/***************** Defines *****************/
// Message IDs (just lower 5 bits)IDs
#define INIT_ENCODER       0X00
#define INIT_PIDP          0x01
#define INIT_PIDI          0x02
#define INIT_PIDD          0x03
#define TX_JOINT_POS       0x04
#define RX_JOINT_POS       0x10


/*********** Function Prototypes ***********/
// HWIs
void CAN_ISR(void);

// SWIs
void CAN_Timer(void);

// Tasks
void CAN_Init(void);
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
Joint Joints[6];

// Message count variables
static volatile uint32_t TX0_Message_Count = 0;
static volatile uint32_t RX0_Mesage_Count = 0;

// Global error flags
static volatile uint32_t CAN_Error_Flag = 0;

// Global receive flag
static volatile bool RX0_Flag = 0;

// Global initialized flag
static bool Init_Flag = 0;

volatile uint32_t CAN_State;


#endif /* INCLUDE_MIRA_CAN_H_ */
