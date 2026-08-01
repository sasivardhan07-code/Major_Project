#include <LPC21XX.H>          // LPC2129 register definitions
#include "types.h"            // User-defined data types
#include "delay.h"            // Delay function declarations
#include "can.h"              // CAN driver functions
#include "can_defines.h"      // CAN register bit definitions


typedef enum                  // Enumeration for indicator operating modes
{
    MODE_OFF = 0,             // Both indicators OFF
    MODE_LEFT,                // Left indicator mode
    MODE_RIGHT                // Right indicator mode
} LED_MODE;

LED_MODE current_mode = MODE_OFF;   // Initialize current mode as OFF

CANF rxF;                     // CAN receive frame structure

int main()
{
   Init_CAN1();               // Initialize CAN1 peripheral

   //InitLCD();               // Initialize LCD (optional)

   while(1)                   // Infinite loop
   {
      if(CAN1_Rx(&rxF))        // Check whether a CAN frame is received
      {
         //CmdLCD(0x80);       // Move LCD cursor (optional)
         //StrLCD("Rx");       // Display "Rx" on LCD (optional)

         if(rxF.ID == 2)       // Check if received CAN ID is 2
         {
            //CmdLCD(0xC0);    // LCD debugging (optional)
            //StrLCD("step 1");// LCD debugging (optional)

            /*CmdLCD(0xC6);    // Display received DATA2 (optional)
            Hex_data(rxF.DATA2);*/

            if(rxF.DATA2 == 0x01)     // Check for Left Indicator command
            {
               //mode = 1;            // Old implementation

               /*CmdLCD(0x88);        // LCD debugging (optional)
               StrLCD("ok");*/

               if(current_mode == MODE_LEFT)   // Already in Left mode?
               {
                  current_mode = MODE_OFF;     // Turn OFF Left Indicator
               }
               else
               {
                  current_mode = MODE_LEFT;    // Enable Left Indicator
               }
            }

            else if(rxF.DATA2 == 0x02)         // Check for Right Indicator command
            {
               //mode = 2;                     // Old implementation

               /*CmdLCD(0x88);                 // LCD debugging (optional)
               StrLCD("yes");*/

               if(current_mode == MODE_RIGHT)  // Already in Right mode?
               {
                  current_mode = MODE_OFF;     // Turn OFF Right Indicator
               }
               else
               {
                  current_mode = MODE_RIGHT;   // Enable Right Indicator
               }
            }
         }
      }

      switch(current_mode)      // Execute function based on current mode
      {
         case MODE_LEFT :        // Left Indicator mode
              left_indicator();  // Blink Left Indicator LEDs
              break;

         case MODE_RIGHT :       // Right Indicator mode
              right_indicator(); // Blink Right Indicator LEDs
              break;

         case MODE_OFF :         // Indicator OFF mode
              led_off();         // Turn OFF all Indicator LEDs
              break;
      }
   }
}
