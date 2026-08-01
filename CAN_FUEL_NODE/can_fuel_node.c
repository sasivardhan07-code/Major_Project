#include <LPC21XX.H>          // LPC2129 register definitions
#include "can.h"              // CAN driver function declarations
#include "can_defines.h"      // CAN register bit definitions
#include "types.h"            // User-defined data types
#include "delay.h"            // Delay function declarations
#include "adc.h"              // ADC driver functions
#include "adc_defines.h"      // ADC register definitions
#include "lcd_defines.h"      // LCD definitions (if required)
#include "lcd.h"              // LCD driver functions (optional)

#define FUEL_MIN 120          // fuel min value i.e it indicates no fuel is there
#define FUEL_MAX 720          // fuel max value i.e car full capacity

#define Tx_LED 16             // CAN Transmit Status LED connected to P0.16

u32 dVal;                     // Stores raw ADC digital value
f32 eAR;                      // Stores equivalent analog voltage
u32 fuel_per;                 // Stores calculated fuel percentage

int main()
{
   //u32 fuel_per;            // Local variable (not used)

   CANF txF;                  // CAN transmit frame structure

   IODIR0 |= 1<<Tx_LED;       // Configure Transmit LED pin as output

   Init_CAN1();               // Initialize CAN1 controller
   Init_ADC();                // Initialize ADC peripheral

   txF.ID = 1;                // Set CAN Identifier to 1
   txF.bfv.RTR = 0;           // Configure as Data Frame (RTR = 0)
   txF.bfv.DLC = 8;           // Set Data Length Code to 8 bytes

   while(1)                   // Infinite loop
   {
      //CAN1_Tx(txF);         // Test CAN transmission (optional)
      //IOPIN0 ^= 1<<Tx_LED;  // Toggle LED for testing (optional)
      //delay_ms(500);        // Delay for testing (optional)

      Read_ADC(1,&dVal,&eAR); // Read ADC Channel 1 and store digital & analog values

      if(dVal <= FUEL_MIN)    // Check if ADC value is below minimum
      {
         fuel_per = 0;        // Fuel level = 0%
      }

      else if(dVal >= FUEL_MAX) // Check if ADC value exceeds maximum
      {
         fuel_per = 100;        // Fuel level = 100%
      }

      else                    // ADC value lies between minimum and maximum
      {
         fuel_per = (((dVal - FUEL_MIN) * 100) / (FUEL_MAX - FUEL_MIN)); // Convert ADC value to fuel percentage
      }

      txF.DATA1 = fuel_per;   // Store fuel percentage in CAN DATA1 byte

      CAN1_Tx(txF);           // Transmit CAN frame

      IOPIN0 ^= 1<<Tx_LED;    // Toggle Transmit LED to indicate CAN transmission

      delay_ms(500);          // Wait for 500 milliseconds
   }
}
