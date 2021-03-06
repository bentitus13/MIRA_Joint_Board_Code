/*
 * MIRA_Joint_Board_Main.c
 *
 * Created on: Feb 11, 2018
 *     Edited: Mar 17, 2018
 *     Author: Ben Titus
 */


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
//#include "include/Board.h"
#include "include/MIRA_CAN.h"
#include "include/MIRA_Current_Sensor.h"
#include "include/MIRA_Encoder.h"
#include "include/MIRA_GPIO.h"
#include "include/MIRA_Load_Cell.h"
#include "include/MIRA_Motor_Control.h"


/***************** Defines *****************/
#define TASKSTACKSIZE    512
#define SAMPLE_FREQUENCY 1000.


/*********** Function Prototypes ***********/
// HWIs

// SWIs
void Heartbeat(void);
void PID_Timer(void);

// Tasks
void Init_Stuff(void);
void Idle_Function(void);
void PID_Calc(void);

// Helper Functions

// Setup Functions


/************* Global Variables ************/
volatile bool heartbeat = false;
int idle_count;
float Kp, Ki, Kd;
uint32_t Setpoint;
float Past_Errors[32];
uint32_t Past_Error_Index;


/******************* HWIs ******************/


/**************** Clock SWIs ***************/
// Heartbeat that blinks the onboard LED at 1Hz
void Heartbeat(void) {
    if (heartbeat) {
        if (Init_Flag) {
            GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_BLUE_PIN, HEARTBEAT_BLUE_PIN);
        } else {
            GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_RED_PIN, HEARTBEAT_RED_PIN);
        }
        GPIOPinWrite(HEARTBEAT1_PORT, HEARTBEAT1_PIN, HEARTBEAT1_PIN);
        heartbeat = false;
    } else {
        GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_BLUE_PIN, 0);
        GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_RED_PIN, 0);
        GPIOPinWrite(HEARTBEAT1_PORT, HEARTBEAT1_PIN, 0);
        heartbeat = true;
    }
}

void PID_Timer(void) {
    Semaphore_post(PID_Semaphore);
}


/****************** Tasks *****************/
// Task that can initialize runtime events
// This should run once then block forever
void Init_Stuff(void) {
    while(1) {
        Semaphore_pend(Init_Semaphore, BIOS_WAIT_FOREVER);
        // Enable interrupts
        IntMasterEnable();
    }
}

void Idle_Function(void) {
    while(1) {
        idle_count++;
    }
}

void PID_Calc(void) {
    float Error = 0.0;
    float Error_Sum = 0.0;
    float P_Val, I_Val, D_Val, Floating_Setpoint;
    float Past_Error = 0.0;
    int i;
    while(1) {
        Semaphore_pend(PID_Semaphore, BIOS_WAIT_FOREVER);
        Past_Error = Error;
        Past_Errors[Past_Error_Index] = Error;
        Past_Error_Index = (32-1) & (Past_Error_Index + 1);

        Error_Sum = 0;
        for (i = 0; i < 32; i++) {
            Error_Sum += Past_Errors[i];
        }

        Floating_Setpoint = (0xFFF & (RX_Joint_Angle_Data - RX_Init_Encoder_Data)) * 360. / 4096.;
        Error = Floating_Setpoint - Joint_Angle;
        Error_Sum += Error;

        P_Val = RX_Init_PIDP_Data * Error;
        I_Val = RX_Init_PIDI_Data * Error_Sum / SAMPLE_FREQUENCY;
        D_Val = RX_Init_PIDD_Data * (Error - Past_Error) * SAMPLE_FREQUENCY;

        if (P_Val > 4095) {
            P_Val = 4095;
        } else if (P_Val < -4095) {
            P_Val = -4095;
        }
        if (I_Val > 4095) {
            I_Val = 4095;
        } else if (I_Val < -4095) {
            I_Val = -4095;
        }
        if (D_Val > 4095) {
            D_Val = 4095;
        } else if (D_Val < -4095) {
            D_Val = -4095;
        }
        Motor_Control = P_Val + I_Val + D_Val;
    }
}


/************* Helper Functions ************/


/************* Setup Functions *************/


// Main, call all setup functions and start BIOS
int main(void) {
    // Disable interrupts
    IntMasterDisable();
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    // Call all setup functions
    Pin_Setup();
    Motor_Setup();
    Current_Sensor_Setup();
    Load_Cell_Setup();
    SSI_Setup();
    CAN_Setup();

    Setpoint = 2048;
    Kp = 45;
    Ki = 8;
    Kd = 3;

    // Start the BIOS
    BIOS_start();

    return (0);
}
