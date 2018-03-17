/*
 * MIRA_Motor_Control.c
 *
 *  Created on: Mar 13, 2018
 *      Author: Ben
 */

#include "include/MIRA_Motor_Control.h"


/******************* HWIs ******************/


/**************** Clock SWIs ***************/
void Motor_Timer(void) {
    Semaphore_post(Motor_Semaphore);
}

/****************** Tasks *****************/
void Motor_Drive(void) {
    while(1) {
        Semaphore_pend(Motor_Semaphore, BIOS_WAIT_FOREVER);
        g_iMotorCtrl = g_iInByte;
        Motor_Out(g_iMotorCtrl);
        g_iMotorCtrl++;
        if (g_iMotorCtrl > 5120)
            g_iMotorCtrl = -5120;
    }
}


/************* Helper Functions ************/
void Motor_Out(int spd) {
    // Constrain spd to -5120 to +5120
    if (spd > MOTOR_MAX_SPD)
        spd = MOTOR_MAX_SPD;
    if (spd < -MOTOR_MAX_SPD)
        spd = -MOTOR_MAX_SPD;
    if (spd == 0)
        spd = 1;

    // Set direction pin and PWM compare value
    if (spd >= 0) {
        // Set direction pin
        GPIOPinWrite(GPIO_PORTB_BASE, MOTOR_DIR_PIN, MOTOR_DIR_PIN);
        // Set PWM value to spd maximum
        PWMPulseWidthSet(PWM0_BASE, PWM_GEN_0, spd);
    } else {
        // Set direction pin
        GPIOPinWrite(GPIO_PORTB_BASE, MOTOR_DIR_PIN, 0);
        // Set PWM value to spd maximum
        PWMPulseWidthSet(PWM0_BASE, PWM_GEN_0, (-spd));
    }
}


/************* Setup Functions *************/

void Motor_Setup(void) {
    // Enable the peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // Set clock to system clock with 32x input divider
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
//    PWMClockSet(PWM_BASE, PWM_SYSCLK_DIV_64);

    //
    PWMDeadBandDisable(PWM0_BASE, PWM_GEN_0);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, MOTOR_MAX_SPD);

    PWMPulseWidthSet(PWM0_BASE, PWM_GEN_0, 1);

    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);

    PWMOutputUpdateMode(PWM0_BASE, PWM_OUT_0_BIT, PWM_OUTPUT_MODE_NO_SYNC);

    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}
