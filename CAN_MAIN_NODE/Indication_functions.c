#include <LPC21XX.H>          // LPC2129 register definitions
#include "can.h"              // CAN driver function declarations
#include "can_defines.h"      // CAN register bit definitions and macros
#include "types.h"            // User-defined data types
#include "delay.h"            // Delay function declarations


void left_indication()        // Function to send Left Indicator CAN message
{
    CANF txF;                 // Declare CAN transmit frame structure

    txF.ID = 2;               // Set CAN Identifier (ID = 2)
    txF.bfv.RTR = 0;          // Data Frame (RTR = 0)
    txF.bfv.DLC = 8;          // Data Length Code = 8 bytes

    txF.DATA2 = 0x01;         // DATA2 = 0x01 indicates Left Indicator ON

    CAN1_Tx(txF);             // Transmit CAN frame
}


void right_indication()       // Function to send Right Indicator CAN message
{
    CANF txF;                 // Declare CAN transmit frame structure

    txF.ID = 2;               // Set CAN Identifier (ID = 2)
    txF.bfv.RTR = 0;          // Data Frame (RTR = 0)
    txF.bfv.DLC = 8;          // Data Length Code = 8 bytes

    txF.DATA2 = 0x02;         // DATA2 = 0x02 indicates Right Indicator ON

    CAN1_Tx(txF);             // Transmit CAN frame
}
