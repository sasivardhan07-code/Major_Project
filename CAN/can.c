#include <LPC21XX.H>        // Contains LPC2129 register definitions
#include "types.h"          // User-defined data types (u8, u16, u32, etc.)
#include "delay.h"          // Delay function declarations
#include "can_defines.h"    // CAN bit positions and macro definitions
#include "can.h"            // CAN frame structure and function declarations


void Init_CAN1(void)
{
    // Configure P0.25 as CAN1 Receive (RD1)
    // PINSEL1 controls alternate functions of P0.16 to P0.31
    PINSEL1 |= RD1_PIN_0_25;

    // Enter Reset Mode before configuring CAN controller
    // RM_BIT = Reset Mode bit
    C1MOD |= (1 << RM_BIT);

    // Enable Acceptance Filter
    // Clear AccOFF bit (Acceptance Filter OFF = 0)
    AFMR &= ~(1 << AccOFF_BIT);

    // Bypass Acceptance Filter
    // Accept all incoming CAN messages
    AFMR |= (1 << AccBP_BIT);

    // Alternative method
    // AFMR = 0x02;
    // (Acceptance Filter Bypass Mode)

    // Set CAN baud rate timing
    // BTR_LVAL contains prescaler, SJW, TSEG1 and TSEG2 values
    C1BTR = BTR_LVAL;

    // Exit Reset Mode
    // CAN controller starts normal operation
    C1MOD &= ~(1 << RM_BIT);
}


void CAN1_Tx(CANF txF)
{
    // Timeout counter to avoid infinite waiting
    u32 wait_time = 500000;

    // Wait until Transmit Buffer 1 becomes free
    while (((C1GSR >> TBS1_BIT) & 1) == 0)
    {
        // If timeout occurs, exit loop
        if (wait_time-- == 0)
        {
            break;
        }
    }

    // Load CAN Identifier (11-bit Standard ID)
    C1TID1 = txF.ID;

    // Configure Transmit Frame Information Register
    // RTR -> Remote Transmission Request bit
    // DLC -> Data Length Code (0-8 bytes)
    C1TFI1 = ((txF.bfv.RTR << RTR_BIT) |
              (txF.bfv.DLC << DLC_BIT));

    // If not a Remote Frame
    if (txF.bfv.RTR != 1)
    {
        // Load first 4 data bytes
        C1TDA1 = txF.DATA1;

        // Load next 4 data bytes
        C1TDB1 = txF.DATA2;
    }

    // Request transmission using Buffer-1
    // STB1 = Select Transmit Buffer 1
    // TR   = Transmission Request
    C1CMR |= ((1 << STB1_BIT) | (1 << TR_BIT));

    // Reset timeout counter
    wait_time = 500000;

    // Wait until transmission is completed
    while (((C1GSR >> TCS1_BIT) & 1) == 0)
    {
        // Timeout protection
        if (wait_time-- == 0)
        {
            break;
        }
    }
}

u8 CAN1_Rx(CANF *rxF)
{
    // Check Receive Buffer Status bit
    // If no message received, return immediately
    if (((C1GSR >> RBS_BIT) & 1) == 0)
        return 0;

    // Read CAN Identifier
    rxF->ID = C1RID;

    // Read RTR bit
    // Determines whether message is Data Frame or Remote Frame
    rxF->bfv.RTR = ((C1RFS >> RTR_BIT) & 1);

    // Read DLC (Number of received bytes)
    rxF->bfv.DLC = ((C1RFS >> DLC_BIT) & 15);

    // If Data Frame
    if (rxF->bfv.RTR == 0)
    {
        // Read first four data bytes
        rxF->DATA1 = C1RDA;

        // Read next four data bytes
        rxF->DATA2 = C1RDB;
    }

    // Release Receive Buffer
    // Allows controller to receive next message
    C1CMR |= (1 << RRB_BIT);

    // Indicate successful reception
    return 1;
}
