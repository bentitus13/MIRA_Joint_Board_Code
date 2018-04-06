/*
 * MIRA_UART.c
 *
 *  Created on: Mar 17, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_UART.h"


/******************* HWIs ******************/
void UART_ISR(void) {
    while (UARTCharsAvail(UART0_BASE)) {
        switch(UART_State) {
        // Initialization
        case 0:
            Global_Init_Data[Init_Data_Index] = UARTCharGetNonBlocking(UART0_BASE);
            Init_Data_Index++;
            if (Init_Data_Index == 20) {
                Init_Data_Index = 0;
                Semaphore_post(UART_Init_Semaphore);
            }
            break;

        // Runtime
        case 1:
            Global_Update_Data[Update_Data_Index] = UARTCharGetNonBlocking(UART0_BASE);
            Update_Data_Index++;
            if (Update_Data_Index == 4) {
                Update_Data_Index = 0;
                Semaphore_post(UART_Update_Semaphore);
            }
            break;
        }
    }
    UARTIntClear(UART0_BASE, UART_INT_RX);
}


/**************** Clock SWIs ***************/
void UART_Timer(void) {
    if (UART_State) {
        Semaphore_post(UART_Transmit_Semaphore);
    }
}


/****************** Tasks *****************/
void UART_Init(void) {
    while(1) {
        Semaphore_pend(UART_Init_Semaphore, BIOS_WAIT_FOREVER);
        int i;
        for (i = 0; i < 20; i++) {
            Init_Data[i] = Global_Init_Data[i];  // Copy to prevent data being overwritten
        }

        if (Init_Data[0] == 'J') {
            Init_Joint_Number = Init_Data[1] - 0x31;

            // Set up ID
            Joints[Init_Joint_Number].Joint_Board_ID = 10*(Init_Data[2]-0x30) + (Init_Data[3]-0x30);

            // Set up transmit ID in upper 6 bits
            Joints[Init_Joint_Number].CAN_TX_Joint.ui32MsgID = Joints[Init_Joint_Number].Joint_Board_ID << 5;

            // Set up receive ID in upper 6 bits
            Joints[Init_Joint_Number].CAN_RX_Joint.ui32MsgID = Joints[Init_Joint_Number].Joint_Board_ID << 5;

            // Set up Encoder offset
            Joints[Init_Joint_Number].TX_Init_Encoder_Data = 1000*(Init_Data[4]-0x30) +
                                                             100*(Init_Data[5]-0x30) +
                                                             10*(Init_Data[6]-0x30) +
                                                             (Init_Data[7]-0x30);

            // Set up PIDP Constant
            Joints[Init_Joint_Number].TX_Init_PIDP_Data = 10*(Init_Data[8]-0x30) +
                                                          (Init_Data[9]-0x30) +
                                                          0.1*(Init_Data[10]-0x30) +
                                                          0.01*(Init_Data[11]-0x30);

            // Set up PIDP Constant
            Joints[Init_Joint_Number].TX_Init_PIDI_Data = 10*(Init_Data[12]-0x30) +
                                                          (Init_Data[13]-0x30) +
                                                          0.1*(Init_Data[14]-0x30) +
                                                          0.01*(Init_Data[15]-0x30);

            // Set up PIDP Constant
            Joints[Init_Joint_Number].TX_Init_PIDD_Data = 10*(Init_Data[16]-0x30) +
                                                          (Init_Data[17]-0x30) +
                                                          0.1*(Init_Data[18]-0x30) +
                                                          0.01*(Init_Data[19]-0x30);

            UART_Print(Ack_Pointer, Ack_Pointer_Length);

//            Init_Data_Index = 0;
            if (Init_Joint_Number == 5) {
                UART_Print(Startup_Message, Startup_Message_Length);
                UART_State = 1;
                Semaphore_post(CAN_Init_Semaphore);
            }

        } else {
            // Error
        }
    }
}

void UART_Transmit(void) {
    while(1) {
        Semaphore_pend(UART_Transmit_Semaphore, BIOS_WAIT_FOREVER);
        int i;
        for (i = 0; i < 6; i++) {
            UART_Print_Num(Joints[i].RX_Data[0]);
        }
    }
}

void UART_Update_Joints(void) {
    while(1) {
        Semaphore_pend(UART_Update_Semaphore, BIOS_WAIT_FOREVER);
        int i;
        for (i = 0; i < 4; i++) {
            Update_Data[i] = Global_Update_Data[i];  // Copy to prevent data being overwritten
        }

        // Set up Encoder offset
        Joints[Joint_Index].TX_Data[0] = 1000*(Update_Data[0]-0x30) +
                                         100*(Update_Data[1]-0x30) +
                                         10*(Update_Data[2]-0x30) +
                                         (Update_Data[3]-0x30);

        Joint_Index++;
        if (Joint_Index == 6) {
            Joint_Index = 0;
        }
    }
}


/************* Helper Functions ************/
void UART_Print(char* str, uint8_t len) {
    int i;
    for (i = 0; i < len; i++) {
        UARTCharPut(UART0_BASE,str[i]);
    }
}

void UART_Print_Num(int num) {
    char numArray[5];
    int i;
    if (num < 0) {
        numArray[0] = '-';
        num = -num;
    } else {
        numArray[0] = ' ';
    }
    for (i = 5; i > 1; i--) {
        numArray[i-1] = (num % 10) + 0x30;
        num /= 10;
    }
    UART_Print(numArray, 5);
}


/************* Setup Functions *************/
void UART_Setup(void) {
    // Enable peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Set UART clock
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Configure UART for 115200 baud, 8n1 operation
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_PAR_NONE));

    // Enable transmit and receive FIFOs
    UARTFIFOEnable(UART0_BASE);

    // Set FIFO receive level to 2
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX2_8);

    // Enable UART receive interrupts
    UARTIntEnable(UART0_BASE, UART_INT_RX);

    // Enable UART0
//    UARTEnable(UART0_BASE);

    // Put character in output buffer
//    UART_Print(Startup_Message, Startup_Message_Length);

    Init_Data_Index = 0;
    Update_Data_Index = 0;
    Joint_Index = 0;
    UART_State = 0;
}

