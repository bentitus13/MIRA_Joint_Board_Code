/*
 * MIRA_Joint_Board_Main.c
 *
 * Created on: Mar 17, 2018
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
#include "include/MIRA_CAN.h"
#include "include/MIRA_GPIO.h"
//#include "include/MIRA_HID.h"
#include "include/MIRA_UART.h"


/***************** Defines *****************/
#define TASKSTACKSIZE   512


/*********** Function Prototypes ***********/
// HWIs

// SWIs
void Heartbeat(void);

// Tasks
void Init_Stuff(void);

// Helper Functions

// Setup Functions


/************* Global Variables ************/
volatile bool heartbeat = false;


/******************* HWIs ******************/


/**************** Clock SWIs ***************/
// Heartbeat that blinks the onboard LED at 1Hz
void Heartbeat(void) {
    if (heartbeat) {
        if (UART_State) {
            GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_BLUE_PIN, HEARTBEAT_BLUE_PIN);
//            UART_Print_Num(33);
        } else {
            GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_RED_PIN, HEARTBEAT_RED_PIN);
//            UART_Print_Num(22);
        }
        heartbeat = false;
    } else {
        GPIOPinWrite(HEARTBEAT_PORT, HEARTBEAT_RED_PIN | HEARTBEAT_BLUE_PIN, 0);
        heartbeat = true;
    }
}


/****************** Tasks *****************/
void Idle_Function(void) {
    while(1) {

    }
}

void Init_Stuff(void) {
    while(1) {
        Semaphore_pend(Init_Semaphore, BIOS_WAIT_FOREVER);
    }
}


/************* Helper Functions ************/


/************* Setup Functions *************/


// Main, call all setup functions and start BIOS
int main(void) {
    // Disable interrupts
    IntMasterDisable();

    // Call all setup functions
    Pin_Setup();
    CAN_Setup();
    UART_Setup();

    IntMasterEnable();

    // Start the BIOS
    BIOS_start();

    return (0);
}
