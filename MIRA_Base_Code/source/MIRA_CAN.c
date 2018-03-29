/*
 * MIRA_CAN.c
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_CAN.h"


/******************* HWIs ******************/
void CAN_ISR(void) {

}


/**************** Clock SWIs ***************/
// Release the CAN task, CAN_Send
void CAN_Timer(void) {
    Semaphore_post(CAN_Semaphore);
}


/****************** Tasks *****************/
void CAN_Send(void) {
    while(1) {
        Semaphore_pend(CAN_Semaphore, BIOS_WAIT_FOREVER);
    }
}


/************* Helper Functions ************/


/************* Setup Functions *************/
void CAN_Setup(void) {

}

