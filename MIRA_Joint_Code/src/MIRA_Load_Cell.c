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

}


/**************** Clock SWIs ***************/
// Release the ADC Task, ADC_Calculate
void ADC_Timer(void) {
    Semaphore_post(ADC_Semaphore);
}


/****************** Tasks *****************/
void ADC_Calculate(void) {
    while(1) {
        Semaphore_pend(ADC_Semaphore, BIOS_WAIT_FOREVER);
    }
}

/************* Helper Functions ************/


/************* Setup Functions *************/
void ADC_Setup(void) {
    // Enable Timer1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerDisable(TIMER1_BASE, TIMER_BOTH);
    // Set clock source
    TimerClockSourceSet(TIMER1_BASE, TIMER_CLOCK_SYSTEM);
    // Set to periodic
    TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);
    // Set the prescaler to 1
    TimerPrescaleSet(TIMER1_BASE, TIMER_A, 0);
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
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) {
//    }

    // Set up Current Sensor
    ADCSequenceDisable(ADC0_BASE, 0);
//    // ADC_PC_SR_125k, ADC_PC_SR_250k, ADC_PC_SR_500k, ADC_PC_SR_1M
//    ADC0_BASE + ADC_O_PC = (ADC_PC_SR_1M);

    // ADC clock
    // Source - internal PIOSC at 16MHz, clock rate full for now
    // Divider - 1 for now, could change later
    // Maybe use PLL if the frequency isn't high enough
//    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 2);

    // Trigger when the processor tells it to (one shot)
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_ALWAYS, 0);

    // Take a sample and interrupt
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH3 | ADC_CTL_IE | ADC_CTL_END);

    // Oversample at 16x (could go higher maybe? lower?)
    ADCHardwareOversampleConfigure(ADC0_BASE, 16);

    // Enable sequence0
    ADCSequenceEnable(ADC0_BASE, 0);

    // Enable interrupts for sequence 0
    ADCIntEnable(ADC0_BASE, 0);
//    ADCIntRegister(ADC0_BASE, 0, &getADC);

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
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH3 | ADC_CTL_IE | ADC_CTL_END);

    // Oversample at 16x (could go higher maybe? lower?)
    ADCHardwareOversampleConfigure(ADC0_BASE, 16);

    // Enable sequence0
    ADCSequenceEnable(ADC0_BASE, 1);

    // Enable interrupts for sequence 0
    ADCIntEnable(ADC0_BASE, 1);
//    ADCIntRegister(ADC0_BASE, 0, &getADC);
}
