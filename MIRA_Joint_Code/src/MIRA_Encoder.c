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
    Encoder_Value &= 0x1FFE;
    Encoder_Value = Encoder_Value >> 1;
    if (Encoder_Value < 4095 && Encoder_Value > 0) {
        // Exponential filter to clean out the spikes in encoder reading
        Encoder_Value = (1-ALPHA) * Encoder_Value + ALPHA * Encoder_Values[Encoder_Index];
        Encoder_Index = 0x07 & (Encoder_Index + 1);
        Encoder_Values[Encoder_Index] = Encoder_Value;
    }
}


/**************** Clock SWIs ***************/
void SSI_Timer(void) {
    Semaphore_post(SSI_Semaphore);
}


/****************** Tasks *****************/
void SSI_Transmit(void) {
    int i;
    uint32_t Temp_Value = 0;
    while(1) {
        // Wait for semaphore
        Semaphore_pend(SSI_Semaphore, BIOS_WAIT_FOREVER);

        // Transmit SSI to request new joint angle
        SSI_Send(READ_ANGLE);

        // Store joint angle in next item of past joint angles
        Past_Angles[Past_Angle_Index] = Joint_Angle;

        // Increment and wrap index
        Past_Angle_Index = (0x1F) & (Past_Angle_Index + 1);

        // Average last 8 values
        Temp_Value = 0;
        for (i = 0; i < 8; i++) {
            Temp_Value += Encoder_Values[i];
        }
        Temp_Value = Temp_Value / 8;

        // Offset Temp_Value by the encoder home position offset
        Temp_Value = (0x0FFF & (Temp_Value - Encoder_Offset));

        // Convert Temp_Value to angle from home position
        Joint_Angle = 360. / 4096. * Temp_Value;
    }
}


/************* Helper Functions ************/
void SSI_Send(uint16_t num) {
    SSIDataPut(SSI0_BASE, num);
}


/************* Setup Functions *************/
void SSI_Setup(void) {
    int i;
    Encoder_Index = 0;
    for (i = 0; i < 8; i++) {
        Encoder_Values[i] = 0;
    }
    Encoder_Offset = 0;
    Past_Angle_Index = 0;
    for (i = 0; i < 32; i++) {
        Past_Angles[i] = 0.0;
    }
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
    SSIIntEnable(SSI0_BASE, SSI_RXFF);
    SSIEnable(SSI0_BASE);
}
