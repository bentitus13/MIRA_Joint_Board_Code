/*
 * MIRA_CAN.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 26, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_CAN_H_
#define INCLUDE_MIRA_CAN_H_

/********** General C Header files *********/
#include <stdbool.h>
#include <stdint.h>


/********** XDCtools Header files **********/
#include <xdc/cfg/global.h>


/************ BIOS Header files ************/
#include <ti/sysbios/BIOS.h>


/*********** TI RTOS Header files **********/
#include <inc/hw_can.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include "driverlib/can.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"


/************ Local Header files ***********/
#include "include/MIRA_GPIO.h"


/***************** Defines *****************/
// Receive message IDs (just lower 5 bits)
//#define RX_ALL_ID           0x01
//#define RX_MOTOR_TORQUE_ID  0x03
#define RX_INIT_ENCODER_ID  0x00
#define RX_INIT_PIDP_ID     0x01
#define RX_INIT_PIDI_ID     0x02
#define RX_INIT_PIDD_ID     0x03
#define RX_JOINT_ANGLE_ID   0x04

// Transmit message IDs
//#define TX_ALL_ID           0x020
//#define TX_MOTOR_TORQUE_ID  0x022
#define TX_JOINT_ANGLE_ID   0x010

// Receive message object numbers
//#define RX_ALL              1
//#define RX_MOTOR_TORQUE     3
#define RX_JOINT_POS        2
#define INIT_PIDP           4
#define INIT_PIDI           5
#define INIT_PIDD           6
#define INIT_ENCODER        7

// Transmit message object numbers
//#define TX_ALL              20
//#define TX_MOTOR_TORQUE     22
#define TX_JOINT_POS        21


/*********** Function Prototypes ***********/
// HWIs
void CAN_ISR(void);

// SWIs
void CAN_Timer(void);

// Tasks
void CAN_Send(void);

// Helper Functions
void CAN_Error_Handler(void);
void CAN_Read_ID(void);
void Setup_TX_All(void);
void Setup_TX_Joint_Angle(void);
void Setup_TX_Motor_Torque(void);
void Setup_RX_All(void);
void Setup_RX_Joint_Pos(void);
void Setup_RX_Motor_Torque(void);
void Setup_RX_Init_PID(void);
void Setup_RX_Init_Encoder(void);
void Send_TX_All(int Joint_Angle, int Motor_Torque);
void Send_TX_Joint_Angle(int Joint_Angle);
void Send_TX_Motor_Torque(int Motor_Torque);

// Setup Functions
void CAN_Setup(void);


/************* Global Variables ************/
// Joint board ID
uint16_t Joint_Board_ID;
uint16_t Message_ID;

// Message count variables
static volatile uint32_t TX0_Message_Count = 0;
static volatile uint32_t RX0_Message_Count = 0;

// Global error flags
static volatile uint32_t CAN_Error_Flag = 0;

// Global receive flag
static volatile bool RX0_Flag = 0;

// Global initialized flag
static bool Init_Flag = 0;

// Data variables
uint16_t TX_All_Data[2];
uint16_t TX_Joint_Pos_Data;
uint16_t TX_Motor_Torque_Data;
uint16_t RX_All_Data[2];
uint16_t RX_Joint_Angle_Data;
uint16_t RX_Motor_Torque_Data;
float RX_Init_PIDP_Data;
float RX_Init_PIDI_Data;
float RX_Init_PIDD_Data;
uint16_t RX_Init_Encoder_Data;
volatile uint32_t CAN_Init;

// CAN transmit message objects
//tCANMsgObject CAN_TX_All;
//tCANMsgObject CAN_TX_Motor_Torque;
tCANMsgObject CAN_TX_Joint_Pos;

// CAN receive message objects
//tCANMsgObject CAN_RX_All;
//tCANMsgObject CAN_RX_Motor_Torque;
tCANMsgObject CAN_RX_Joint_Pos;
tCANMsgObject CAN_RX_Init_PIDP;
tCANMsgObject CAN_RX_Init_PIDI;
tCANMsgObject CAN_RX_Init_PIDD;
tCANMsgObject CAN_RX_Init_Encoder;



#endif /* INCLUDE_MIRA_CAN_H_ */
