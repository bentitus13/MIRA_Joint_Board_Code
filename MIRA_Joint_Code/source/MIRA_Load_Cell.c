/*
 * MIRA_Load_Cell.c
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 17, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_Load_Cell.h"


/******************* HWIs ******************/
void Load_Cell_ISR(void) {
    ADCIntClear(ADC0_BASE, 1);
    ADCSequenceDataGet(ADC0_BASE, 1, &Load_Cell_Value);
    Load_Cell_Values[Load_Cell_Index] = Load_Cell_Value;
    Load_Cell_Index = 0x07 & (Load_Cell_Value + 1);
}


/**************** Clock SWIs ***************/
// Release the ADC Task, ADC_Calculate
void Load_Cell_Timer(void) {
    Semaphore_post(Load_Cell_Semaphore);
}


/****************** Tasks *****************/
void Load_Cell_Calculate(void) {
    int i;
    uint32_t Temp_Value;
    while(1) {
        Semaphore_pend(Load_Cell_Semaphore, BIOS_WAIT_FOREVER);
        Temp_Value = 0;
        for (i = 0; i < 8; i++) {
            Temp_Value += Load_Cell_Values[i];
        }
        Load_Cell_Force = Temp_Value / 8;
    }
}

/************* Helper Functions ************/


/************* Setup Functions *************/
void Load_Cell_Setup(void) {
    // Enable Timer1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerDisable(TIMER1_BASE, TIMER_BOTH);
    // Set clock source
    TimerClockSourceSet(TIMER1_BASE, TIMER_CLOCK_SYSTEM);
    // Set to periodic
    TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);
    // Set the prescaler to 1
    TimerPrescaleSet(TIMER1_BASE, TIMER_A, 1);
    // Set load value
    TimerLoadSet(TIMER1_BASE, TIMER_A, 0x0FFFF);
    // Set time to trigger ADC
    TimerControlTrigger(TIMER1_BASE, TIMER_A, true);
    // Set compare value
//    TimerMatchSet(TIMER1_BASE, TIMER_A, 0x07FFF);
//    // Enable timeout interrupt
//    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
//    // Register ISR
//    TimerIntRegister(TIMER1_BASE, TIMER_A, &timerISR);
    // Enable Timer1A
    TimerEnable(TIMER1_BASE, TIMER_A);

    // Initialize ADC0 Module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

//    // Wait for the module to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) {
    }

    // Set up Load Cell
    ADCSequenceDisable(ADC0_BASE, 1);
//    // ADC_PC_SR_125k, ADC_PC_SR_250k, ADC_PC_SR_500k, ADC_PC_SR_1M
//    ADC0_BASE + ADC_O_PC = (ADC_PC_SR_1M);

    // ADC clock
    // Source - internal PIOSC at 16MHz, clock rate full for now
    // Divider - 1 for now, could change later
    // Maybe use PLL if the frequency isn't high enough
//    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 2);

    // Trigger when the processor tells it to (one shot)
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_ALWAYS, 0);

    // Take a sample and interrupt
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);

    // Oversample at 16x (could go higher maybe? lower?)
    ADCHardwareOversampleConfigure(ADC0_BASE, 16);

    // Enable sequence0
    ADCSequenceEnable(ADC0_BASE, 1);

    // Enable interrupts for sequence 0
    ADCIntEnable(ADC0_BASE, 1);
//    ADCIntRegister(ADC0_BASE, 0, &getADC);
}
