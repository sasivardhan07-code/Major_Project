#include <LPC21XX.H>          // LPC2129 register definitions
#include "can.h"              // CAN function declarations
#include "delay.h"            // Delay function declarations
#include "types.h"            // User-defined data types

#define LED      0            // LEDs are connected starting from P0.0
#define LED_SET  (0xFF << LED) // Mask for LEDs P0.0 to P0.7

static s32 position = 0;      // Current LED position (0 to 7)
static u8 pattern = 0;        // Stores LED ON pattern

void led_off(void)            // Function to turn OFF all LEDs
{
    IOSET0 = LED_SET;         // Active LOW LEDs, so setting bits turns OFF all LEDs
}

void left_indicator(void)     // Function to generate Left Indicator pattern
{
    IODIR0 |= LED_SET;        // Configure LED pins (P0.0-P0.7) as outputs

    pattern |= (1 << position); // Turn ON the current LED in the pattern

    IOSET0 = LED_SET;         // Turn OFF all LEDs before updating pattern
    IOCLR0 = pattern << LED;  // Turn ON selected LEDs (Active LOW)

    position++;               // Move to the next LED position

    if(position >= 8)         // Check if the last LED has been reached
    {
        delay_ms(300);        // Keep all LEDs ON for 300 ms

        position = 0;         // Reset position to the first LED
        pattern = 0;          // Clear the LED pattern

        led_off();            // Turn OFF all LEDs
    }

    delay_ms(100);            // Delay to create LED running effect
}

void right_indicator(void)    // Function to generate Right Indicator pattern
{
    IODIR0 |= LED_SET;        // Configure LED pins (P0.0-P0.7) as outputs

    pattern |= (1 << position); // Turn ON the current LED in the pattern

    IOSET0 = LED_SET;         // Turn OFF all LEDs before updating pattern
    IOCLR0 = pattern << LED;  // Turn ON selected LEDs (Active LOW)

    position--;               // Move to the previous LED position

    if(position < 0)          // Check if the first LED has been crossed
    {
        delay_ms(300);        // Keep all LEDs ON for 300 ms

        position = 7;         // Restart from the last LED
        pattern = 0;          // Clear the LED pattern

        led_off();            // Turn OFF all LEDs
    }

    delay_ms(100);            // Delay to create LED running effect
}
