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

    if (Status == Joints[0].RX_Object_Number) { // message received

        // Set message data pointer
        Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[0].RX_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, Joints[0].RX_Object_Number, &Joints[0].CAN_TX_Joint, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
    } else if (Status == Joints[1].RX_Object_Number) { // message received

        // Set message data pointer
        Joints[1].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[1].RX_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, Joints[1].RX_Object_Number, &Joints[1].CAN_TX_Joint, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
    } else if (Status == Joints[2].RX_Object_Number) { // message received

        // Set message data pointer
        Joints[2].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[2].RX_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, Joints[2].RX_Object_Number, &Joints[2].CAN_TX_Joint, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
    } else if (Status == Joints[3].RX_Object_Number) { // message received

        // Set message data pointer
        Joints[3].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[3].RX_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, Joints[3].RX_Object_Number, &Joints[3].CAN_TX_Joint, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
    } else if (Status == Joints[4].RX_Object_Number) { // message received

        // Set message data pointer
        Joints[4].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[4].RX_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, Joints[4].RX_Object_Number, &Joints[4].CAN_TX_Joint, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
    } else if (Status == Joints[5].RX_Object_Number) { // message received

        // Set message data pointer
        Joints[5].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[5].RX_Data;

        // Get message data
        CANMessageGet(CAN0_BASE, Joints[5].RX_Object_Number, &Joints[5].CAN_TX_Joint, 1);

        // Increment received message count
        RX0_Mesage_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;

        // Set flag that message was reeived
//        RX0_Flag = 1;
    } else if (Status == Joints[0].TX_Object_Number) {
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, Joints[0].TX_Object_Number, &Joints[0].CAN_TX_Joint, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, Joints[0].TX_Object_Number);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
    } else if (Status == Joints[1].TX_Object_Number) {
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, Joints[1].TX_Object_Number, &Joints[1].CAN_TX_Joint, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, Joints[1].TX_Object_Number);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
    } else if (Status == Joints[2].TX_Object_Number) {
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, Joints[2].TX_Object_Number, &Joints[2].CAN_TX_Joint, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, Joints[2].TX_Object_Number);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
    } else if (Status == Joints[3].TX_Object_Number) {
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, Joints[3].TX_Object_Number, &Joints[3].CAN_TX_Joint, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, Joints[3].TX_Object_Number);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
    } else if (Status == Joints[4].TX_Object_Number) {
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, Joints[4].TX_Object_Number, &Joints[4].CAN_TX_Joint, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, Joints[4].TX_Object_Number);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
    } else if (Status == Joints[5].TX_Object_Number) {
        // Set message type to RX so that it doesn't continually transmit messages
        CANMessageSet(CAN0_BASE, Joints[5].TX_Object_Number, &Joints[5].CAN_TX_Joint, MSG_OBJ_TYPE_RX);

        // Clear the message object interrupt.
        CANIntClear(CAN0_BASE, Joints[5].TX_Object_Number);

        // Increment a counter to keep track of how many messages have been transmitted.
        TX0_Message_Count++;

        // Since a message was transmitted, clear any error flags.
        CAN_Error_Flag = 0;
    } else {

     // status or other interrupt: clear it and set error flags
        CAN_Error_Flag |= CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        CAN_Error_Handler();
        CANIntClear(CAN0_BASE, Status);
    }

}


/**************** Clock SWIs ***************/
// Release the CAN task, CAN_Send
void CAN_Timer(void) {
    if (CAN_State == 4) {
        Semaphore_post(CAN_Transmit_Semaphore);
    } else {
        if (UART_State) {
            Semaphore_post(CAN_Init_Semaphore);
        }
    }
}


/****************** Tasks *****************/
void CAN_Init(void) {
    while(1) {
        Semaphore_pend(CAN_Init_Semaphore, BIOS_WAIT_FOREVER);
        if (UART_State) {
            int i;
            switch (CAN_State) {
            case 0:
                // Set message data pointers for encoder offset
                for (i = 0; i < 6; i++) {
                    Joints[i].CAN_TX_Joint.ui32MsgID &= 0x7E0;
                    Joints[i].CAN_TX_Joint.ui32MsgID |= INIT_ENCODER;
                    Joints[i].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[i].TX_Init_Encoder_Data);
                    Joints[i].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[i].TX_Init_Encoder_Data;
                    CANMessageSet(CAN0_BASE, Joints[i].TX_Object_Number, &Joints[i].CAN_TX_Joint, MSG_OBJ_TYPE_TX);
                }
                CAN_State = 1;
                break;

            case 1:

                for (i = 0; i < 6; i++) {
                    Joints[i].CAN_TX_Joint.ui32MsgID &= 0x7E0;
                    Joints[i].CAN_TX_Joint.ui32MsgID |= INIT_PIDP;
                    Joints[i].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[i].TX_Init_PIDP_Data);
                    Joints[i].CAN_TX_Joint.pui8MsgData = (uint8_t *) &Joints[i].TX_Init_PIDP_Data;
                    CANMessageSet(CAN0_BASE, Joints[i].TX_Object_Number, &Joints[i].CAN_TX_Joint, MSG_OBJ_TYPE_TX);
                }
                CAN_State = 2;
                break;

            case 2:
                for (i = 0; i < 6; i++) {
                    Joints[i].CAN_TX_Joint.ui32MsgID &= 0x7E0;
                    Joints[i].CAN_TX_Joint.ui32MsgID |= INIT_PIDI;
                    Joints[i].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[i].TX_Init_PIDI_Data);
                    Joints[i].CAN_TX_Joint.pui8MsgData = (uint8_t *) &Joints[i].TX_Init_PIDI_Data;
                    CANMessageSet(CAN0_BASE, Joints[i].TX_Object_Number, &Joints[i].CAN_TX_Joint, MSG_OBJ_TYPE_TX);
                }
                CAN_State = 3;
                break;

            case 3:
                for (i = 0; i < 6; i++) {
                    Joints[i].CAN_TX_Joint.ui32MsgID &= 0x7E0;
                    Joints[i].CAN_TX_Joint.ui32MsgID |= INIT_PIDD;
                    Joints[i].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[i].TX_Init_PIDD_Data);
                    Joints[i].CAN_TX_Joint.pui8MsgData = (uint8_t *) &Joints[i].TX_Init_PIDD_Data;
                    CANMessageSet(CAN0_BASE, Joints[i].TX_Object_Number, &Joints[i].CAN_TX_Joint, MSG_OBJ_TYPE_TX);
                }
                CAN_State = 4;
                break;
            default:
                break;
            }
        }
    }
}

void CAN_Send(void) {
    while(1) {
        Semaphore_pend(CAN_Transmit_Semaphore, BIOS_WAIT_FOREVER);
        // Only transmit if there are no errors
        if (CAN_Error_Flag == 0) {
            // Set message data pointers
            int i;
            for (i = 0; i < 6; i++) {
                Joints[i].CAN_TX_Joint.ui32MsgID &= 0x7E0;
                Joints[i].CAN_TX_Joint.ui32MsgID |= TX_JOINT_POS;
                Joints[i].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[i].TX_Data[0]);
                Joints[i].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[i].TX_Data[0];
                CANMessageSet(CAN0_BASE, Joints[i].TX_Object_Number, &Joints[i].CAN_TX_Joint, MSG_OBJ_TYPE_TX);
                Joints[i].TX_Data[0] += 1;
                Joints[i].TX_Data[0] &= 4095;
            }
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

// Set up the TX_All message object
void Setup_TX_Joint1(void) {
    Joints[0].CAN_TX_Joint.ui32MsgID = 0;                                // Set ID to Base module address
    Joints[0].CAN_TX_Joint.ui32MsgIDMask = 0;                            // Set mask to 0, doesn't matter for this
    Joints[0].CAN_TX_Joint.ui32Flags = MSG_OBJ_TX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[0].TX_Data);       // Set length to 1 byte
    Joints[0].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[0].TX_Data;  // Set the message data pointer
}

// Set up the TX_All message object
void Setup_TX_Joint2(void) {
    Joints[1].CAN_TX_Joint.ui32MsgID = 0;                                // Set ID to Base module address
    Joints[1].CAN_TX_Joint.ui32MsgIDMask = 0;                            // Set mask to 0, doesn't matter for this
    Joints[1].CAN_TX_Joint.ui32Flags = MSG_OBJ_TX_INT_ENABLE;            // Set TX interrupt flag
    Joints[1].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[1].TX_Data);       // Set length to 1 byte
    Joints[1].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[1].TX_Data;  // Set the message data pointer
}

// Set up the TX_All message object
void Setup_TX_Joint3(void) {
    Joints[2].CAN_TX_Joint.ui32MsgID = 0;                                // Set ID to Base module address
    Joints[2].CAN_TX_Joint.ui32MsgIDMask = 0;                            // Set mask to 0, doesn't matter for this
    Joints[2].CAN_TX_Joint.ui32Flags = MSG_OBJ_TX_INT_ENABLE;            // Set TX interrupt flag
    Joints[2].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[2].TX_Data);       // Set length to 1 byte
    Joints[2].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[2].TX_Data;  // Set the message data pointer
}

// Set up the TX_All message object
void Setup_TX_Joint4(void) {
    Joints[3].CAN_TX_Joint.ui32MsgID = 0;                                // Set ID to Base module address
    Joints[3].CAN_TX_Joint.ui32MsgIDMask = 0;                            // Set mask to 0, doesn't matter for this
    Joints[3].CAN_TX_Joint.ui32Flags = MSG_OBJ_TX_INT_ENABLE;            // Set TX interrupt flag
    Joints[3].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[3].TX_Data);       // Set length to 1 byte
    Joints[3].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[3].TX_Data;  // Set the message data pointer
}

// Set up the TX_All message object
void Setup_TX_Joint5(void) {
    Joints[4].CAN_TX_Joint.ui32MsgID = 0;                                // Set ID to Base module address
    Joints[4].CAN_TX_Joint.ui32MsgIDMask = 0;                            // Set mask to 0, doesn't matter for this
    Joints[4].CAN_TX_Joint.ui32Flags = MSG_OBJ_TX_INT_ENABLE;            // Set TX interrupt flag
    Joints[4].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[4].TX_Data);       // Set length to 1 byte
    Joints[4].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[4].TX_Data;  // Set the message data pointer
}

// Set up the TX_All message object
void Setup_TX_Joint6(void) {
    Joints[5].CAN_TX_Joint.ui32MsgID = 0;                                // Set ID to Base module address
    Joints[5].CAN_TX_Joint.ui32MsgIDMask = 0;                            // Set mask to 0, doesn't matter for this
    Joints[5].CAN_TX_Joint.ui32Flags = MSG_OBJ_TX_INT_ENABLE;            // Set TX interrupt flag
    Joints[5].CAN_TX_Joint.ui32MsgLen = sizeof(Joints[5].TX_Data);       // Set length to 1 byte
    Joints[5].CAN_TX_Joint.pui8MsgData = (uint8_t *) Joints[5].TX_Data;  // Set the message data pointer
}

// Set up the TX_All message object
void Setup_RX_Joint1(void) {
    Joints[0].CAN_RX_Joint.ui32MsgID = RX_JOINT_POS;                     // Set ID to Base module address
    Joints[0].CAN_RX_Joint.ui32MsgIDMask = 0x7E0;                        // Set mask to 0, doesn't matter for this
    Joints[0].CAN_RX_Joint.ui32Flags = MSG_OBJ_RX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_RX_Joint.ui32MsgLen = sizeof(Joints[0].RX_Data);       // Set length to 1 byte
    Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[0].RX_Data;  // Set the message data pointer
    CANMessageSet(CAN0_BASE, Joints[0].RX_Object_Number, &Joints[0].CAN_RX_Joint, MSG_OBJ_TYPE_RX);
}

// Set up the TX_All message object
void Setup_RX_Joint2(void) {
    Joints[0].CAN_RX_Joint.ui32MsgID = RX_JOINT_POS;                     // Set ID to Base module address
    Joints[0].CAN_RX_Joint.ui32MsgIDMask = 0x7E0;                        // Set mask to 0, doesn't matter for this
    Joints[0].CAN_RX_Joint.ui32Flags = MSG_OBJ_RX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_RX_Joint.ui32MsgLen = sizeof(Joints[1].RX_Data);       // Set length to 1 byte
    Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[1].RX_Data;  // Set the message data pointer
    CANMessageSet(CAN0_BASE, Joints[1].RX_Object_Number, &Joints[1].CAN_RX_Joint, MSG_OBJ_TYPE_RX);
}

// Set up the TX_All message object
void Setup_RX_Joint3(void) {
    Joints[0].CAN_RX_Joint.ui32MsgID = RX_JOINT_POS;                     // Set ID to Base module address
    Joints[0].CAN_RX_Joint.ui32MsgIDMask = 0x7E0;                        // Set mask to 0, doesn't matter for this
    Joints[0].CAN_RX_Joint.ui32Flags = MSG_OBJ_RX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_RX_Joint.ui32MsgLen = sizeof(Joints[2].RX_Data);       // Set length to 1 byte
    Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[2].RX_Data;  // Set the message data pointer
    CANMessageSet(CAN0_BASE, Joints[2].RX_Object_Number, &Joints[2].CAN_RX_Joint, MSG_OBJ_TYPE_RX);
}

// Set up the TX_All message object
void Setup_RX_Joint4(void) {
    Joints[0].CAN_RX_Joint.ui32MsgID = RX_JOINT_POS;                     // Set ID to Base module address
    Joints[0].CAN_RX_Joint.ui32MsgIDMask = 0x7E0;                        // Set mask to 0, doesn't matter for this
    Joints[0].CAN_RX_Joint.ui32Flags = MSG_OBJ_RX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_RX_Joint.ui32MsgLen = sizeof(Joints[3].RX_Data);       // Set length to 1 byte
    Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[3].RX_Data;  // Set the message data pointer
    CANMessageSet(CAN0_BASE, Joints[3].RX_Object_Number, &Joints[3].CAN_RX_Joint, MSG_OBJ_TYPE_RX);
}

// Set up the TX_All message object
void Setup_RX_Joint5(void) {
    Joints[0].CAN_RX_Joint.ui32MsgID = RX_JOINT_POS;                     // Set ID to Base module address
    Joints[0].CAN_RX_Joint.ui32MsgIDMask = 0x7E0;                        // Set mask to 0, doesn't matter for this
    Joints[0].CAN_RX_Joint.ui32Flags = MSG_OBJ_RX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_RX_Joint.ui32MsgLen = sizeof(Joints[4].RX_Data);       // Set length to 1 byte
    Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[4].RX_Data;  // Set the message data pointer
    CANMessageSet(CAN0_BASE, Joints[4].RX_Object_Number, &Joints[4].CAN_RX_Joint, MSG_OBJ_TYPE_RX);
}

// Set up the TX_All message object
void Setup_RX_Joint6(void) {
    Joints[0].CAN_RX_Joint.ui32MsgID = RX_JOINT_POS;                     // Set ID to Base module address
    Joints[0].CAN_RX_Joint.ui32MsgIDMask = 0x7E0;                        // Set mask to 0, doesn't matter for this
    Joints[0].CAN_RX_Joint.ui32Flags = MSG_OBJ_RX_INT_ENABLE;            // Set TX interrupt flag
    Joints[0].CAN_RX_Joint.ui32MsgLen = sizeof(Joints[5].RX_Data);       // Set length to 1 byte
    Joints[0].CAN_RX_Joint.pui8MsgData = (uint8_t *) Joints[5].RX_Data;  // Set the message data pointer
    CANMessageSet(CAN0_BASE, Joints[5].RX_Object_Number, &Joints[5].CAN_RX_Joint, MSG_OBJ_TYPE_RX);
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

    // Set all Joint object field values to 0
    int i;
    for (i = 0; i < 6; i++) {
        Joints[i].TX_Object_Number = i + 21;
        Joints[i].RX_Object_Number = i + 1;

        Joints[i].Joint_Board_ID = 0;

        // Message ID, bit-shifted joint board ID
        Joints[i].Message_ID = 0;

        // Data variables
        Joints[i].TX_Data[0] = 0;
        Joints[i].TX_Data[1] = 0;
        Joints[i].RX_Data[0] = 0;
        Joints[i].RX_Data[1] = 0;
        Joints[i].TX_Init_PIDP_Data = 0.0;
        Joints[i].TX_Init_PIDI_Data = 0.0;
        Joints[i].TX_Init_PIDD_Data = 0.0;
        Joints[i].TX_Init_Encoder_Data = 0;
    }

    Setup_TX_Joint1();
    Setup_TX_Joint2();
    Setup_TX_Joint3();
    Setup_TX_Joint4();
    Setup_TX_Joint5();
    Setup_TX_Joint6();
    Setup_RX_Joint1();
    Setup_RX_Joint2();
    Setup_RX_Joint3();
    Setup_RX_Joint4();
    Setup_RX_Joint5();
    Setup_RX_Joint6();

    CAN_State = 0;
}

