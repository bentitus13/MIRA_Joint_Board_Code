/*
 * MIRA_Load_Cell.h
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#ifndef INCLUDE_MIRA_LOAD_CELL_H_
#define INCLUDE_MIRA_LOAD_CELL_H_



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
#include <inc/hw_memmap.h>
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"


/************ Local Header files ***********/


/***************** Defines *****************/


/*********** Function Prototypes ***********/
// HWIs
void Load_Cell_ISR(void);

// SWIs
void Load_Cell_Timer(void);

// Tasks
void Load_Cell_Calculate(void);

// Helper Functions

// Setup Functions
void Load_Cell_Setup(void);


/************* Global Variables ************/
uint32_t Load_Cell_Value;

uint32_t Load_Cell_Values[8];

uint32_t Load_Cell_Index;

uint32_t Load_Cell_Force;


#endif /* INCLUDE_MIRA_LOAD_CELL_H_ */
