#include <LPC21XX.H>              // LPC2129 register definitions
#include "interrupt_defines.h"    // External interrupt macros and definitions
#include "interrupt.h"            // Interrupt function declarations
#include "delay.h"                // Delay function declarations
#include "can.h"                  // CAN driver functions
#include "lcd.h"                  // LCD driver functions
#include "types.h"                // User-defined data types

volatile u32 flag1 = 0;           // Flag indicating EINT0 (Left Indicator) interrupt occurred
volatile u32 flag2 = 0;           // Flag indicating EINT2 (Right Indicator) interrupt occurred
volatile u32 blink1 = 0;          // Left Indicator blinking status
volatile u32 blink2 = 0;          // Right Indicator blinking status

void eint0_isr(void) __irq        // Interrupt Service Routine for EINT0
{
    flag1 = 1;                    // Set Left Indicator flag

    blink1 = !blink1;             // Toggle Left Indicator blink status

    blink2 = 0;                   // Turn OFF Right Indicator blinking

    EXTINT = 1 << 0;              // Clear EINT0 interrupt flag

    VICVectAddr = 0;              // Notify VIC that ISR execution is complete
}

void eint2_isr(void) __irq        // Interrupt Service Routine for EINT2
{
    flag2 = 1;                    // Set Right Indicator flag

    blink2 = !blink2;             // Toggle Right Indicator blink status

    blink1 = 0;                   // Turn OFF Left Indicator blinking

    EXTINT = 1 << 2;              // Clear EINT2 interrupt flag

    VICVectAddr = 0;              // Notify VIC that ISR execution is complete
}

void Init_EXT_INT(void)           // Function to initialize External Interrupts
{
    PINSEL0 |= EINT0_0_1 | EINT2_0_7;        // Configure P0.1 as EINT0 and P0.7 as EINT2

    VICIntEnable = (1 << EINT0_VIC_CHNO) |  // Enable EINT0 interrupt in VIC
                   (1 << EINT2_VIC_CHNO);   // Enable EINT2 interrupt in VIC

    VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO; // Enable vector slot 0 and assign EINT0 channel

    VICVectAddr0 = (u32)eint0_isr;            // Assign EINT0 ISR address to vector slot 0

    VICVectCntl2 = (1 << 5) | EINT2_VIC_CHNO; // Enable vector slot 2 and assign EINT2 channel

    VICVectAddr2 = (u32)eint2_isr;            // Assign EINT2 ISR address to vector slot 2

    EXTMODE = (1 << 0) | (1 << 2);            // Configure EINT0 and EINT2 as edge-triggered interrupts
}
