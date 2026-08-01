#include <LPC21XX.H>          // LPC2129 register definitions
#include "types.h"            // User-defined data types
#include "delay.h"            // Delay function declarations
#include "lcd.h"              // LCD driver functions
#include "can.h"              // CAN driver functions
#include "can_defines.h"      // CAN register bit definitions
#include "interrupt.h"        // External interrupt functions
#include "i2c.h"              // I2C driver functions
#include "MMA7660.h"          // MMA7660 accelerometer driver

#define LED1    21            // LED connected to P0.21
#define Rx_LED  23            // CAN Receive LED connected to P0.23

extern volatile u32 flag1;    // Left indicator interrupt flag
extern volatile u32 flag2;    // Right indicator interrupt flag
extern volatile u32 blink1;   // Left indicator blinking status
extern volatile u32 blink2;   // Right indicator blinking status

CANF rxF;                     // CAN receive frame structure

int main()
{
   s8 fuel, fuel_block, i;                    // Variables for fuel value and LCD blocks

   IODIR0 |= (1<<LED1) | (1<<Rx_LED);         // Configure LED pins as outputs

   InitLCD();                                // Initialize 20x4 LCD
   WriteToCGRAM();                           // Load custom characters into LCD
   Init_CAN1();                              // Initialize CAN1 controller
   Init_i2c();                               // Initialize I2C peripheral
   Init_EXT_INT();                           // Initialize external interrupts
   Init_mma7660();                           // Initialize MMA7660 accelerometer

   while(1)                                  // Infinite loop
   {
      if(flag1)                              // Check left indicator interrupt
      {
         flag1 = 0;                          // Clear left interrupt flag
         left_indication();                  // Start left indicator blinking
      }

      if(flag2)                              // Check right indicator interrupt
      {
         flag2 = 0;                          // Clear right interrupt flag
         right_indication();                 // Start right indicator blinking
      }

      IOSET0 = 1<<LED1;                      // Turn ON status LED
      delay_ms(500);                         // Wait for 500 ms

      airbag_trigger();                      // Check accelerometer for airbag trigger

      if(CAN1_Rx(&rxF))                      // Check whether CAN message is received
      {
         fuel = rxF.DATA1;                   // Read fuel percentage from DATA1

         IOPIN0 ^= (1<<Rx_LED);              // Toggle receive LED
         delay_ms(500);                      // Wait for 500 ms

         //CmdLCD(0x01);                     // LCD clear (optional)

         CmdLCD(0xC0);                       // Move cursor to second line
         StrLCD("Fuel:");                    // Display "Fuel:"

         //if(fuel>100)                      // Optional fuel limit check
         //   fuel=100;

         fuel_block = fuel/25;               // Convert fuel % into four LCD blocks

         for(i=0;i<4;i++)                    // Display four fuel blocks
         {
            if(i<fuel_block)                 // Filled block?
               CharLCD(i+4);                 // Display custom filled block

            else
               CharLCD(' ');                 // Display blank space
         }

         CmdLCD(0xCA);                       // Move cursor after fuel bar
         IntLCD(fuel);                       // Display fuel percentage
         StrLCD("%");                        // Display '%' symbol
         CharLCD(' ');                       // Display one blank space
      }

      CmdLCD(0x80);                          // Move cursor to first line
      StrLCD("------DASHBOARD-----");        // Display dashboard title

      CmdLCD(0x94);                          // Move cursor to third line
      StrLCD("AIRBAG STATUS:");              // Display airbag label

      CmdLCD(0xA3);                          // Position cursor
      StrLCD("OFF");                         // Display airbag status OFF

      CmdLCD(0xA6);                          // Position cursor
      CharLCD(3);                            // Display custom airbag symbol

      CmdLCD(0xD4);                          // Move cursor to fourth line
      StrLCD("Indicator:");                  // Display indicator label

      CmdLCD(0xDE);                          // Position cursor
      CharLCD(0);                            // Display left arrow symbol

      CmdLCD(0xE0);                          // Position cursor
      CharLCD(1);                            // Display center symbol

      CmdLCD(0xE2);                          // Position cursor
      CharLCD(2);                            // Display right arrow symbol

      if(blink1)                             // Check left blink status
      {
         CmdLCD(0xDE);                       // Position cursor at left arrow
         CharLCD(' ');                       // Hide left arrow
         delay_ms(500);                      // Wait 500 ms
         CmdLCD(0xDE);                       // Position cursor again
         CharLCD(0);                         // Display left arrow
      }
      else
      {
         CmdLCD(0xDE);                       // Position cursor
         CharLCD(0);                         // Keep left arrow visible
      }

      if(blink2)                             // Check right blink status
      {
         CmdLCD(0xE2);                       // Position cursor at right arrow
         CharLCD(' ');                       // Hide right arrow
         delay_ms(500);                      // Wait 500 ms
         CmdLCD(0xE2);                       // Position cursor again
         CharLCD(2);                         // Display right arrow
      }
      else
      {
         CmdLCD(0xE2);                       // Position cursor
         CharLCD(2);                         // Keep right arrow visible
      }
   }
}
