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
    uint32_t Status;

    // Read the CAN interrupt status to find the cause of the interrupt
    Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    switch(Status) {
    case RX0OBJECT: // message received

        // Set message data pointer
        CAN_RX0_Message.pui8MsgData = (uint8_t *) RX0_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, RX0OBJECT, &CAN_RX0_Message, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
        break;

    case TX0OBJECT:
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, TX0OBJECT, &CAN_TX0_Message, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, TX0OBJECT);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
        break;

    default: // status or other interrupt: clear it and set error flags
        CAN_Error_Flag |= CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        CAN_Error_Handler();
        CANIntClear(CAN0_BASE, Status);
    }
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
        // Only transmit if there are no errors
        if (CAN_Error_Flag == 0) {

            // Set message data pointer
            CAN_TX0_Message.pui8MsgData = (uint8_t *) TX0_Data;

            // Send the CAN message using object number 2
            CANMessageSet(CAN0_BASE, TX0OBJECT, &CAN_TX0_Message, MSG_OBJ_TYPE_TX);
        }
    }
}


/************* Helper Functions ************/

// Error handler for CAN errors
// Fill in with what to do
void CAN_Error_Handler(void) {

    // If the bus is off (Too many errors happened)
    if(CAN_Error_Flag & CAN_STATUS_BUS_OFF) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_BUS_OFF);
    }

    // If there have been many of errors (more than 96)
    if(CAN_Error_Flag & CAN_STATUS_EWARN) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_EWARN);
    }

    // If there have been a lot of errors (more than 127)
    if(CAN_Error_Flag & CAN_STATUS_EPASS) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_EPASS);
    }

    // Received message successfully
    if(CAN_Error_Flag & CAN_STATUS_RXOK) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_RXOK);
    }

    // Transmit message successfully
    if(CAN_Error_Flag & CAN_STATUS_TXOK) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_TXOK);
    }

    // Check the LEC
    if(CAN_Error_Flag & CAN_STATUS_LEC_MSK) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_MSK);
    }

    // Bit stuffing error
    if(CAN_Error_Flag & CAN_STATUS_LEC_STUFF) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_STUFF);
    }

    // Formatting error
    if(CAN_Error_Flag & CAN_STATUS_LEC_FORM) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_FORM);
    }

    // Acknowledge error
    if(CAN_Error_Flag & CAN_STATUS_LEC_ACK) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_ACK);
    }

    // The bus remained a bit level of 1 for longer than is allowed.
    if(CAN_Error_Flag & CAN_STATUS_LEC_BIT1) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_BIT1);
    }

    // The bus remained a bit level of 0 for longer than is allowed.
    if(CAN_Error_Flag & CAN_STATUS_LEC_BIT0) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_BIT0);
    }

    // CRC error
    if(CAN_Error_Flag & CAN_STATUS_LEC_CRC) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_CRC);
    }

    // LEC mask
    if(CAN_Error_Flag & CAN_STATUS_LEC_MASK) {
        // Clear the flag
        CAN_Error_Flag &= ~(CAN_STATUS_LEC_MASK);
    }

    // If there are any bits still set in CAN_Error_Flag then something unhandled has happened.
    if(CAN_Error_Flag !=0) {
        // Handle this here, shouldn't ever get here
    }
}


/************* Setup Functions *************/
void CAN_Setup(void) {
    // Enable CAN0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

    CANInit(CAN0_BASE);             // Initialize CAN0 controller
    CANBitRateSet(CAN0_BASE,        // Set CAN0 to run at 1Mbps
                  SysCtlClockGet(),
                  1000000);
    CANIntEnable(CAN0_BASE,         // Enable interrupts, error interrupts, and status interrupts
                 CAN_INT_MASTER |
                 CAN_INT_ERROR  |
                 CAN_INT_STATUS);

    // Enable CAN0 interrupt in interrupt controller
    IntEnable(INT_CAN0);

    // Enable CAN0
    CANEnable(CAN0_BASE);

    // Set up TX0 message object
    CAN_TX0_Message.ui32MsgID = CANTX0ID;                // Set ID to 2
    CAN_TX0_Message.ui32MsgIDMask = 0;                   // Set mask to 0, doesn't matter for this
    CAN_TX0_Message.ui32Flags = MSG_OBJ_TX_INT_ENABLE;    // Set TX interrupt flag
    CAN_TX0_Message.ui32MsgLen = sizeof(TX0_Data);       // Set length to 1 byte
    CAN_TX0_Message.pui8MsgData = (uint8_t *) TX0_Data;              // Set the message data pointer

    // Set up RX0 message object
    CAN_RX0_Message.ui32MsgID = CANRX0ID;                // Set ID to Any
    CAN_RX0_Message.ui32MsgIDMask = 0;                   // Set mask to any
    CAN_RX0_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE |  // Set RX Interrupt and use ID filter flags
                                 MSG_OBJ_USE_ID_FILTER;
    CAN_RX0_Message.ui32MsgLen = sizeof(RX0_Data);        // Set length to 1 byte
    CAN_RX0_Message.pui8MsgData = (uint8_t *) RX0_Data;              // Set the message data pointer

    // Load message 1 with g_sCAN0RxMessage settings
    CANMessageSet(CAN0_BASE, RX0OBJECT, &CAN_RX0_Message, MSG_OBJ_TYPE_RX);
}

