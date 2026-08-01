#include <LPC21XX.H>              // LPC2129 register definitions
#include "i2c.h"                  // I2C driver function declarations
#include "delay.h"                // Delay function declarations
#include "MMA7660.h"              // MMA7660 function declarations
#include "MMA7660_defines.h"      // MMA7660 register and address definitions

void mma7660_write(u8 reg, u8 data)    // Function to write one byte to MMA7660 register
{
    i2c_start();                       // Generate I2C START condition

    i2c_write(MMA7660_SA);             // Send MMA7660 slave address (Write mode)

    i2c_write(reg);                    // Send register address

    i2c_write(data);                   // Send data to the selected register

    i2c_stop();                        // Generate I2C STOP condition

    delay_ms(2);                       // Wait for write operation to complete
}

u8 mma7660_read(u8 reg)                // Function to read one byte from MMA7660 register
{
    u8 data;                           // Variable to store received data

    i2c_start();                       // Generate START condition

    i2c_write(MMA7660_SA);             // Send slave address (Write mode)

    i2c_write(reg);                    // Send register address to read

    i2c_restart();                     // Generate Repeated START condition

    i2c_write(MMA7660_SA_R);           // Send slave address (Read mode)

    data = i2c_nack();                 // Read one byte and send NACK (last byte)

    i2c_stop();                        // Generate STOP condition

    delay_ms(2);                       // Small delay

    return data;                       // Return received register value
}

void Init_mma7660(void)                // Function to initialize MMA7660
{
    delay_ms(10);                      // Wait after power-up

    mma7660_write(MMA_MODE, 0x00);     // Put sensor into Standby mode

    delay_ms(10);                      // Wait for mode change

    mma7660_write(MMA_SR, 0x00);       // Set Sample Rate Register

    mma7660_write(MMA_MODE, 0x01);     // Enable Active mode

    delay_ms(10);                      // Wait for sensor stabilization
}

s8 convert_data(u8 val)                // Convert 6-bit sensor data to signed 8-bit value
{
    val &= 0x3F;                       // Mask upper two bits (keep only 6-bit data)

    if(val & 0x20)                     // Check sign bit (bit-5)
        val |= 0xC0;                   // Sign-extend to 8-bit value

    return (s8)val;                    // Return signed acceleration value
}

s8 mma7660_get_x(void)                 // Read X-axis acceleration
{
    return convert_data(mma7660_read(MMA_XOUT));   // Read XOUT register and convert data
}

s8 mma7660_get_y(void)                 // Read Y-axis acceleration
{
    return convert_data(mma7660_read(MMA_YOUT));   // Read YOUT register and convert data
}

s8 mma7660_get_z(void)                 // Read Z-axis acceleration
{
    return convert_data(mma7660_read(MMA_ZOUT));   // Read ZOUT register and convert data
}
