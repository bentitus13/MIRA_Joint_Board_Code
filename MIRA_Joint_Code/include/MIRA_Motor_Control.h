/*
 * MIRA_Motor_Control.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_MOTOR_CONTROL_H_
#define INCLUDE_MIRA_MOTOR_CONTROL_H_


/********** General C Header files *********/
#include <stdbool.h>
#include <stdint.h>


/********** XDCtools Header files **********/
#include <xdc/cfg/global.h>


/************ BIOS Header files ************/
#include <ti/sysbios/BIOS.h>


/*********** TI RTOS Header files **********/
#include "driverlib/pwm.h"


/************ Local Header files ***********/
#include "include/MIRA_GPIO.h"


/***************** Defines *****************/
#define MOTOR_MAX_SPD  4096       // Max speed of motor (PWM timer reset value)


/*********** Function Prototypes ***********/
// HWIs

// SWIs
void Motor_Timer(void);
// Tasks
void Motor_Drive(void);

// Helper Functions
void Motor_Out(int spd);

// Setup Functions
void Motor_Setup(void);


/************* Global Variables ************/
int Motor_Control;

#endif /* INCLUDE_MIRA_CAN_H_ */
