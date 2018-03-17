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
#define TASKSTACKSIZE   512


/*********** Function Prototypes ***********/
// HWIs

// SWIs
void Heartbeat(void);

// Tasks

// Helper Functions

// Setup Functions


/************* Global Variables ************/
bool heartbeat = false;


/******************* HWIs ******************/


/**************** Clock SWIs ***************/
// Heartbeat that blinks the onboard LED at 1Hz
void Heartbeat(void) {
    if (heartbeat) {
        GPIOPinWrite(GPIO_PORTF_BASE, HEARTBEAT_PIN, HEARTBEAT_PIN);
        heartbeat = false;
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, HEARTBEAT_PIN, 0);
        heartbeat = true;
    }
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


/************* Helper Functions ************/


/************* Setup Functions *************/


// Main, call all setup functions and start BIOS
int main(void) {
    // Disable interrupts
    IntMasterDisable();

    // Call all setup functions
    Pin_Setup();
    Motor_Setup();
    ADC_Setup();
    SSI_Setup();
    UART_Setup();


    // Start the BIOS
    BIOS_start();

    return (0);
}
