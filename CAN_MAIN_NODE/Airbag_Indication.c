#include <LPC21XX.H>          // LPC2129 register definitions
#include "types.h"            // User-defined data types
#include "delay.h"            // Delay function declarations
#include "can.h"              // CAN driver functions
#include "lcd.h"              // LCD driver functions
#include "i2c.h"              // I2C driver functions
#include "lcd_defines.h"      // LCD command definitions
#include "MMA7660.h"          // MMA7660 accelerometer driver

#define LED0 22               // Airbag status LED connected to P0.22

s8 x, y, z;                   // Variables to store X, Y and Z acceleration values

void airbag_trigger()         // Function to detect accident and trigger airbag
{
     IODIR0 |= 1<<LED0;       // Configure LED0 pin as output

     x = mma7660_get_x();     // Read X-axis acceleration value
     y = mma7660_get_y();     // Read Y-axis acceleration value
     z = mma7660_get_z();     // Read Z-axis acceleration value

     // Check whether acceleration exceeds ±25 on any axis
     if((x <= -25 || x >= 25) || (y <= -25 || y >= 25) || (z <= -25 || z >= 25))
     {
          IOSET0 = 1<<LED0;   // Turn ON airbag indicator LED

          //CmdLCD(0x01);     // Clear LCD (optional)

          CmdLCD(0xA3);       // Move LCD cursor to Airbag Status position
          StrLCD("ON ");      // Display "ON" on LCD

          CmdLCD(0xA6);       // Move cursor to Airbag symbol position
          CharLCD(255);       // Display full-block symbol (airbag activated)

          //CharLCD(3);       // Alternative custom airbag symbol
          //StrLCD(" ");      // Optional blank space

          delay_ms(1000);     // Keep status displayed for 1 second

          //CmdLCD(0x01);     // Clear LCD (optional)
     }
}
