/*
 * MIRA_Encoder.c
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_Encoder.h"


/******************* HWIs ******************/
void SSI_ISR(void) {
    SSIDataGet(SSI0_BASE, &Encoder_Value);
    Encoder_Value &= 0x0FFF;
    Joint Angle = 360. / 4096. * (Encoder_Value - Encoder_Offset);
}


/**************** Clock SWIs ***************/
void SSI_Timer(void) {
    Semaphore_post(SSI_Semaphore);
}


/****************** Tasks *****************/
void SSI_Transmit(void) {
    while(1) {
        Semaphore_pend(SSI_Semaphore, BIOS_WAIT_FOREVER);
        SSI_Send(READ_ANGLE);
    }
}


/************* Helper Functions ************/
void SSI_Send(uint16_t num) {
    SSIDataPut(SSI0_BASE, num);
}


/************* Setup Functions *************/
void SSI_Setup(void) {
    // Enable peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    // Set clock to system clock
    SSIClockSourceSet(SSI0_BASE, SSI_CLOCK_SYSTEM);

    /*  Configure SSI:
     *  Clock speed -> System clock
     *  Mode -> polarity 0, phase 0
     *
     */
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 5000000, 16);
    SSIEnable(SSI0_BASE);
}
