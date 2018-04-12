/*
 * MIRA_CAN.c
 *
 *  Created on: Mar 13, 2018
 *      Edited: Mar 26, 2018
 *      Author: Ben Titus
 */

#include "include/MIRA_CAN.h"


/******************* HWIs ******************/
void CAN_ISR(void) {
    uint32_t Status;

    // Read the CAN interrupt status to find the cause of the interrupt
    Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    switch(Status) {
    case RX_JOINT_POS: // message received
        // Set message data pointer
        CAN_RX_Joint_Pos.pui8MsgData = (uint8_t *) RX_Joint_Angle_Data;

        IntMasterDisable();

        // Get message data
        CANMessageGet(CAN0_BASE, RX_JOINT_POS, &CAN_RX_Joint_Pos, 1);

        IntMasterEnable();

        // Increment received message count
        RX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
        break;

    case INIT_ENCODER:
        // Set the message data pointer
        CAN_RX_Init_Encoder.pui8MsgData = (uint8_t *) &RX_Init_Encoder_Data;

        IntMasterDisable();

        // Get message data
        CANMessageGet(CAN0_BASE, INIT_ENCODER, &CAN_RX_Init_Encoder, 1);

        IntMasterEnable();

        // Increment a counter to keep track of how many messages have been received.
        RX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set a bit high in CAN_Setup
        CAN_Init |= 0x01;
        break;

    case INIT_PIDP:
        // Set the message pointer
        CAN_RX_Init_PIDP.pui8MsgData = (uint8_t *) &RX_Init_PIDP_Data;

        IntMasterDisable();

        // Get message data
        CANMessageGet(CAN0_BASE, INIT_PIDP, &CAN_RX_Init_PIDP, 1);

        IntMasterEnable();

        // Increment a counter to keep track of how many messages have been received.
        RX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set a bit high in CAN_Setup
        CAN_Init |= 0x02;
        break;

    case INIT_PIDI:
        // Set the message pointer
        CAN_RX_Init_PIDI.pui8MsgData = (uint8_t *) &RX_Init_PIDI_Data;

        IntMasterDisable();

        // Get message data
        CANMessageGet(CAN0_BASE, INIT_PIDI, &CAN_RX_Init_PIDI, 1);

        IntMasterEnable();

        // Increment a counter to keep track of how many messages have been received.
        RX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set a bit high in CAN_Setup
        CAN_Init |= 0x04;
        break;

    case INIT_PIDD:
        // Set the message pointer
        CAN_RX_Init_PIDD.pui8MsgData = (uint8_t *) &RX_Init_PIDD_Data;

        IntMasterDisable();

        // Get message data
        CANMessageGet(CAN0_BASE, INIT_PIDD, &CAN_RX_Init_PIDD, 1);

        IntMasterEnable();

        // Increment a counter to keep track of how many messages have been received.
        RX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set a bit high in CAN_Setup
        CAN_Init |= 0x08;
        break;

    case TX_JOINT_POS:
        // Set to receive so the controller doesn't spam messages
        CANMessageSet(CAN0_BASE, TX_JOINT_POS, &CAN_TX_Joint_Pos, MSG_OBJ_TYPE_RX);

        // Clear the interrupt
        CANIntClear(CAN0_BASE, TX_JOINT_POS);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

    default: // status or other interrupt: clear it and set error flags
        CAN_Error_Flag |= CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        CAN_Error_Handler();
        IntMasterDisable();
        CANIntClear(CAN0_BASE, Status);
        IntMasterEnable();
    }
}


/**************** Clock SWIs ***************/
// Release the CAN task, CAN_Send
void CAN_Timer(void) {
    if (CAN_Init == 0x0F) {
        Semaphore_post(CAN_Semaphore);
    }
}


/****************** Tasks *****************/
void CAN_Send(void) {
    while(1) {
        Semaphore_pend(CAN_Semaphore, BIOS_WAIT_FOREVER);
        // Only transmit if there are no errors
        if (CAN_Error_Flag == 0) {

            // Set message data pointer
            CAN_TX_Joint_Pos.pui8MsgData = (uint8_t *) TX_Joint_Pos_Data;

            // Send the CAN message using object number 2
            CANMessageSet(CAN0_BASE, TX_JOINT_POS, &CAN_TX_Joint_Pos, MSG_OBJ_TYPE_TX);
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

// Reads in the joint board ID
void CAN_Read_ID(void) {
    Joint_Board_ID = 0;
    if (GPIOPinRead(SW1_PORT, SW1_PIN)) {
        Joint_Board_ID |= 0x01;
    }
    if (GPIOPinRead(SW2_PORT, SW2_PIN)) {
        Joint_Board_ID |= 0x02;
    }
    if (GPIOPinRead(SW3_PORT, SW3_PIN)) {
        Joint_Board_ID |= 0x04;
    }
    if (GPIOPinRead(SW4_PORT, SW4_PIN)) {
        Joint_Board_ID |= 0x08;
    }
    if (GPIOPinRead(SW5_PORT, SW5_PIN)) {
        Joint_Board_ID |= 0x10;
    }
    if (GPIOPinRead(SW6_PORT, SW6_PIN)) {
        Joint_Board_ID |= 0x20;
    }
    Message_ID = (Joint_Board_ID << 5) & 0x7E0;
}

void Setup_TX_Joint_Pos(void) {
    CAN_TX_Joint_Pos.ui32MsgID = TX_JOINT_ANGLE_ID;                            // Set ID to Base module address
    CAN_TX_Joint_Pos.ui32MsgIDMask = 0;                                        // Set mask to 0, doesn't matter for this
    CAN_TX_Joint_Pos.ui32Flags = MSG_OBJ_TX_INT_ENABLE;                        // Set TX interrupt flag
    CAN_TX_Joint_Pos.ui32MsgLen = sizeof(TX_Joint_Pos_Data);                   // Set length to 1 byte
    CAN_TX_Joint_Pos.pui8MsgData = (uint8_t *) TX_Joint_Pos_Data;              // Set the message data pointer
}

void Setup_RX_Joint_Pos(void) {
    CAN_RX_Joint_Pos.ui32MsgID = Message_ID | RX_JOINT_ANGLE_ID;               // Set ID to Base module address
    CAN_RX_Joint_Pos.ui32MsgIDMask = 0xFFF;                                    // Set mask to 0, doesn't matter for this
    CAN_RX_Joint_Pos.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;                        // Set TX interrupt flag
    CAN_RX_Joint_Pos.ui32MsgLen = sizeof(RX_Joint_Angle_Data);                 // Set length to 1 byte
    CAN_RX_Joint_Pos.pui8MsgData = (uint8_t *) RX_Joint_Angle_Data;            // Set the message data pointer
    CANMessageSet(CAN0_BASE, RX_JOINT_POS, &CAN_RX_Joint_Pos, MSG_OBJ_TYPE_RX);
}

void Setup_RX_Init_PIDP(void) {
    CAN_RX_Init_PIDP.ui32MsgID = Message_ID | RX_INIT_PIDP_ID;                 // Set ID to Base module address
    CAN_RX_Init_PIDP.ui32MsgIDMask = 0xFFF;                                    // Set mask to 0, doesn't matter for this
    CAN_RX_Init_PIDP.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;                        // Set TX interrupt flag
    CAN_RX_Init_PIDP.ui32MsgLen = sizeof(RX_Init_PIDP_Data);                   // Set length to 1 byte
    CAN_RX_Init_PIDP.pui8MsgData = (uint8_t *) &RX_Init_PIDP_Data;             // Set the message data pointer
    CANMessageSet(CAN0_BASE, INIT_PIDP, &CAN_RX_Init_PIDP, MSG_OBJ_TYPE_RX);
}

void Setup_RX_Init_PIDI(void) {
    CAN_RX_Init_PIDI.ui32MsgID = Message_ID | RX_INIT_PIDI_ID;                 // Set ID to Base module address
    CAN_RX_Init_PIDI.ui32MsgIDMask = 0xFFF;                                    // Set mask to 0, doesn't matter for this
    CAN_RX_Init_PIDI.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;                        // Set TX interrupt flag
    CAN_RX_Init_PIDI.ui32MsgLen = sizeof(RX_Init_PIDI_Data);                   // Set length to 1 byte
    CAN_RX_Init_PIDI.pui8MsgData = (uint8_t *) &RX_Init_PIDI_Data;             // Set the message data pointer
    CANMessageSet(CAN0_BASE, INIT_PIDI, &CAN_RX_Init_PIDI, MSG_OBJ_TYPE_RX);
}

void Setup_RX_Init_PIDD(void) {
    CAN_RX_Init_PIDD.ui32MsgID = Message_ID | RX_INIT_PIDD_ID;                 // Set ID to Base module address
    CAN_RX_Init_PIDD.ui32MsgIDMask = 0xFFF;                                    // Set mask to 0, doesn't matter for this
    CAN_RX_Init_PIDD.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;                        // Set TX interrupt flag
    CAN_RX_Init_PIDD.ui32MsgLen = sizeof(RX_Init_PIDD_Data);                   // Set length to 1 byte
    CAN_RX_Init_PIDD.pui8MsgData = (uint8_t *) &RX_Init_PIDD_Data;             // Set the message data pointer
    CANMessageSet(CAN0_BASE, INIT_PIDD, &CAN_RX_Init_PIDD, MSG_OBJ_TYPE_RX);
}

void Setup_RX_Init_Encoder(void) {
    CAN_RX_Init_Encoder.ui32MsgID = Message_ID | RX_INIT_ENCODER_ID;           // Set ID to Base module address
    CAN_RX_Init_Encoder.ui32MsgIDMask = 0xFFF;                                     // Set mask to 0, doesn't matter for this
    CAN_RX_Init_Encoder.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;                     // Set TX interrupt flag
    CAN_RX_Init_Encoder.ui32MsgLen = sizeof(RX_Init_Encoder_Data);             // Set length to 1 byte
    CAN_RX_Init_Encoder.pui8MsgData = (uint8_t *) RX_Init_Encoder_Data;        // Set the message data pointer
    CANMessageSet(CAN0_BASE, INIT_ENCODER, &CAN_RX_Init_Encoder, MSG_OBJ_TYPE_RX);
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

    CAN_Init = 0;

    CAN_Read_ID();

    Setup_TX_Joint_Pos();
    Setup_RX_Joint_Pos();
    Setup_RX_Init_PIDP();
    Setup_RX_Init_PIDI();
    Setup_RX_Init_PIDD();
    Setup_RX_Init_Encoder();
}

