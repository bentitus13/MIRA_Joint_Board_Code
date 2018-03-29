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
// Receive message IDs (just lower 5 bits)
#define RX_ALL_ID           0x01
#define RX_JOINT_ANGLE_ID   0x02
#define RX_MOTOR_TORQUE_ID  0x03
#define RX_INIT_PIDP_ID     0x04
#define RX_INIT_PIDI_ID     0x05
#define RX_INIT_PIDD_ID     0x06
#define RX_INIT_ENCODER_ID  0x07

// Transmit message IDs
#define TX_ALL_ID           0x020
#define TX_JOINT_ANGLE_ID   0x021
#define TX_MOTOR_TORQUE_ID  0x022

// Receive message object numbers
#define RX_ALL              1
#define RX_JOINT_ANGLE      2
#define RX_MOTOR_TORQUE     3
#define RX_INIT_PIDP        4
#define RX_INIT_PIDI        5
#define RX_INIT_PIDD        6
#define RX_INIT_ENCODER     7

// Transmit message object numbers
#define TX_ALL              20
#define TX_JOINT_ANGLE      21
#define TX_MOTOR_TORQUE     22


/*********** Function Prototypes ***********/
// HWIs
void CAN_ISR(void);

// SWIs
void CAN_Timer(void);

// Tasks
void CAN_Send(void);

// Helper Functions


// Setup Functions
void CAN_Setup(void);


/**************** Structs ******************/
typedef struct Joint {
    // Joint board ID, raw number (0-63)
    uint16_t Joint_Board_ID;

    // Message ID, bit-shifted joint board ID
    uint16_t Message_ID;

    // Data variables
    uint16_t TX_All_Data[2];
    uint16_t TX_Joint_Angle_Data;
    uint16_t TX_Motor_Torque_Data;
    uint16_t RX_All_Data[2];
    uint16_t RX_Joint_Angle_Data;
    uint16_t RX_Motor_Torque_Data;
    float RX_Init_PIDP_Data;
    float RX_Init_PIDI_Data;
    float RX_Init_PIDD_Data;
    uint16_t RX_Init_Encoder_Data;

    // CAN transmit message objects
    tCANMsgObject CAN_TX_All;
    tCANMsgObject CAN_TX_Update;
    tCANMsgObject CAN_TX_Motor_Torque;

    // CAN receive message objects
    tCANMsgObject CAN_RX_All;
    tCANMsgObject CAN_RX_Joint_Angle;
    tCANMsgObject CAN_RX_Motor_Torque;
    tCANMsgObject CAN_RX_Init_PIDP;
    tCANMsgObject CAN_RX_Init_PIDI;
    tCANMsgObject CAN_RX_Init_PIDD;
    tCANMsgObject CAN_RX_Init_Encoder;
};


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


#endif /* INCLUDE_MIRA_CAN_H_ */
