#include <LPC21XX.H>          // LPC2129 register definitions
#include "i2c_defines.h"      // I2C register bit definitions and macros
#include "types.h"            // User-defined data types

void Init_i2c(void)           // Function to initialize the I2C peripheral
{
   PINSEL0 |= SCL_0_2 | SDA_0_3;     // Configure P0.2 as SCL and P0.3 as SDA

   I2SCLH = I2C_DIVIDER;             // Set HIGH period of SCL clock
   I2SCLL = I2C_DIVIDER;             // Set LOW period of SCL clock

   I2CONSET = 1 << I2EN_BIT;         // Enable I2C interface
}

void i2c_start(void)          // Function to generate I2C START condition
{
   I2CONSET = 1 << STA_BIT;          // Set START condition

   while(!(I2CONSET & (1 << SI_BIT))); // Wait until START condition is transmitted

   I2CONCLR = 1 << STAC_BIT;         // Clear START flag
}

void i2c_restart(void)        // Function to generate I2C REPEATED START condition
{
   I2CONSET = 1 << STA_BIT;          // Generate Repeated START condition

   I2CONCLR = 1 << SIC_BIT;          // Clear SI flag

   while(!(I2CONSET & (1 << SI_BIT))); // Wait until Repeated START is completed

   I2CONCLR = 1 << STAC_BIT;         // Clear START flag
}

void i2c_stop(void)           // Function to generate I2C STOP condition
{
   I2CONSET = 1 << STO_BIT;          // Generate STOP condition

   I2CONCLR = 1 << SIC_BIT;          // Clear SI flag
}

void i2c_write(u8 dat)        // Function to transmit one byte over I2C
{
   I2DAT = dat;                      // Load data into I2C data register

   I2CONCLR = 1 << SIC_BIT;          // Clear SI flag to start transmission

   while(!(I2CONSET & (1 << SI_BIT))); // Wait until transmission completes
}

u8 i2c_nack(void)             // Function to receive one byte and send NACK
{
   I2CONCLR = 1 << SIC_BIT;          // Clear SI flag to receive data

   while(!(I2CONSET & (1 << SI_BIT))); // Wait until data is received

   return I2DAT;                     // Return received byte (NACK indicates last byte)
}

u8 i2c_mack(void)             // Function to receive one byte and send ACK
{
   I2CONSET = 1 << AA_BIT;           // Send ACK after receiving data

   I2CONCLR = 1 << SIC_BIT;          // Clear SI flag

   while(!(I2CONSET & (1 << SI_BIT))); // Wait until data is received

   I2CONCLR = 1 << AAC_BIT;          // Clear ACK bit

   return I2DAT;                     // Return received byte
}
