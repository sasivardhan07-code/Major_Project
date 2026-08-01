#include <LPC21XX.H>          // LPC2129 register definitions
#include "delay.h"            // Delay function declarations
#include "adc_defines.h"      // ADC register bit definitions and macros
#include "types.h"            // User-defined data types
#include "adc.h"              // ADC function declarations

void Init_ADC(void)           // Function to initialize the ADC peripheral
{
    PINSEL1 &= ~(0xFF << 22);                 // Clear pin function bits for P0.27-P0.30
    PINSEL1 |= (AIN1_0_28);                   // Configure P0.28 as ADC Channel-1 (AD0.1)
    //PINSEL1 |= (AIN0_0_27)|(AIN1_0_28)|(AIN2_0_29)|(AIN3_0_30); // Configure multiple ADC channels (optional)

    ADCR |= (CLKDIV << CLKDIV_BITS_START) |   // Set ADC clock divider
            (1 << PDN_BIT);                   // Power ON the ADC module
}

void Read_ADC(u32 chNo, u32 *dVal, f32 *eAR)  // Function to read ADC value
{
    ADCR &= 0xFFFFFF00;                       // Clear previously selected ADC channels

    ADCR |= (1 << chNo) |                     // Select the required ADC channel
            (1 << CONV_START_BIT);            // Start ADC conversion

    delay_us(3);                              // Small delay for conversion start

    while(((ADDR >> DONE_BIT) & 1) == 0);     // Wait until ADC conversion is complete

    ADCR &= ~(1 << CONV_START_BIT);           // Stop ADC conversion

    *dVal = ((ADDR >> RESULT_BITS_START) & 1023); // Extract 10-bit digital ADC result

    *eAR = ((*dVal) * (3.3 / 1023));          // Convert digital value into analog voltage (0-3.3V)
}
