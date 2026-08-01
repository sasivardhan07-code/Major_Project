#include "types.h"              // User-defined data types (u32, etc.)

void delay_us(u32 tdly)         // Function to generate delay in microseconds
{
    tdly = tdly * 12;           // Convert microseconds into loop count (for 12 MHz clock)

    while(tdly--);              // Execute empty loop until delay expires
}

void delay_ms(u32 tdly)         // Function to generate delay in milliseconds
{
    tdly = tdly * 12000;        // Convert milliseconds into loop count (for 12 MHz clock)

    while(tdly--);              // Execute empty loop until delay expires
}

void delay_s(u32 tdly)          // Function to generate delay in seconds
{
    tdly = tdly * 12000000;     // Convert seconds into loop count (for 12 MHz clock)

    while(tdly--);              // Execute empty loop until delay expires
}
