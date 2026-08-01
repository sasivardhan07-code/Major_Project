#include <LPC21XX.H>                  // LPC2129 register definitions
#include "delay.h"                   // Delay function declarations
#include "types.h"                   // User-defined data types
#include "defines.h"                 // General macro definitions
#include "lcd.h"                     // LCD function declarations
#include "lcd_defines.h"             // LCD pin definitions

void InitLCD(void)                   // Function to initialize LCD
{
    IODIR0 |= (0xFF<<LCD_DATA) | (1<<RS) | (1<<RW) | (1<<EN); // Configure LCD data and control pins as outputs

    delay_ms(15);                    // Wait for LCD power stabilization

    CmdLCD(0x30);                    // Function set command
    delay_ms(5);                     // Delay

    CmdLCD(0x30);                    // Function set command
    delay_ms(1);                     // Delay

    CmdLCD(0x30);                    // Function set command
    delay_ms(1);                     // Delay

    CmdLCD(0x38);                    // 8-bit mode, 2-line display, 5x7 font
    CmdLCD(0x01);                    // Clear display
    CmdLCD(0x06);                    // Cursor move right
    CmdLCD(0x0C);                    // Display ON, Cursor OFF
}

void DispLCD(u8 val)                 // Function to send data/command to LCD
{
    IOCLR0 = 1<<RW;                  // Select Write mode

    WRITEBYTE(IOPIN0, LCD_DATA, val); // Write data to LCD data pins

    IOSET0 = 1<<EN;                  // Enable HIGH
    delay_us(2);                     // Short delay
    IOCLR0 = 1<<EN;                  // Enable LOW

    delay_ms(2);                     // Wait for LCD execution
}

void CmdLCD(u8 cmd)                  // Function to send command to LCD
{
    IOCLR0 = 1<<RS;                  // RS = 0 for command mode
    DispLCD(cmd);                    // Send command
}

void CharLCD(s8 data)                // Function to send character to LCD
{
    IOSET0 = 1<<RS;                  // RS = 1 for data mode
    DispLCD(data);                   // Send character
}

void StrLCD(s8 *ptr)                 // Function to display string
{
    while(*ptr != '\0')              // Loop until string ends
    {
        CharLCD(*ptr);               // Display character
        ptr++;                       // Move to next character
    }
}

void IntLCD(s32 num)                 // Function to display integer number
{
    s8 a[10];                        // Array to store digits
    s32 i = 0;                       // Index variable

    if(num == 0)                     // Check for zero
    {
        CharLCD('0');                // Display 0
    }
    else
    {
        if(num < 0)                  // Check negative number
        {
            CharLCD('-');            // Display minus sign
            num = -num;              // Convert to positive
        }

        while(num)                   // Extract digits
        {
            a[i++] = num%10 + 48;    // Store ASCII digit
            num /= 10;               // Remove last digit
        }

        --i;                         // Point to last digit

        for(; i>=0; i--)             // Display digits in reverse order
        {
            CharLCD(a[i]);           // Display digit
        }
    }
}

void WriteToCGRAM(void)              // Function to create custom LCD symbols
{
    s8 i;                            // Loop variable

    s8 a[] = {0x00,0x06,0x0E,0x1E,0x1E,0x0E,0x06,0x00}; // Left indicator
    s8 b[] = {0x00,0x04,0x0E,0x1F,0x1F,0x0E,0x04,0x00}; // Center symbol
    s8 c[] = {0x00,0x0C,0x0E,0x0F,0x0F,0x0E,0x0C,0x00}; // Right indicator
    s8 d[] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x11,0x1F}; // Airbag symbol
    s8 e[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00}; // Fuel block 25%
    s8 f[] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00}; // Fuel block 50%
    s8 g[] = {0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00}; // Fuel block 75%
    s8 h[] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00}; // Fuel block 100%

    CmdLCD(0x40);                    // Move to CGRAM address

    for(i=0;i<8;i++) CharLCD(a[i]); // Store symbol 0
    for(i=0;i<8;i++) CharLCD(b[i]); // Store symbol 1
    for(i=0;i<8;i++) CharLCD(c[i]); // Store symbol 2
    for(i=0;i<8;i++) CharLCD(d[i]); // Store symbol 3
    for(i=0;i<8;i++) CharLCD(e[i]); // Store symbol 4
    for(i=0;i<8;i++) CharLCD(f[i]); // Store symbol 5
    for(i=0;i<8;i++) CharLCD(g[i]); // Store symbol 6
    for(i=0;i<8;i++) CharLCD(h[i]); // Store symbol 7
}

void FloatLCD(f32 fN, u32 nDP)       // Function to display floating-point number
{
    u32 n;                           // Integer part
    s32 i;                           // Loop variable

    if(fN < 0.0)                     // Check negative number
    {
        CharLCD('-');                // Display minus sign
        fN = -fN;                    // Convert to positive
    }

    n = fN;                          // Extract integer part
    IntLCD(n);                       // Display integer part

    CharLCD('.');                    // Display decimal point

    for(i=0;i<nDP;i++)               // Display decimal digits
    {
        fN = (fN - n) * 10;          // Shift decimal digit
        n = fN;                      // Extract digit
        CharLCD(n + 48);             // Display digit
    }
}

void HexLCD(u8 data)                 // Function to display hexadecimal byte
{
    u8 up, low;                      // Upper and lower nibbles

    up = (data >> 4) & 0x0F;         // Extract upper nibble
    low = data & 0x0F;              // Extract lower nibble

    if(up < 10)
        DispLCD(up + '0');           // Display 0-9
    else
        DispLCD(up - 10 + 'A');      // Display A-F

    if(low < 10)
        DispLCD(low + '0');          // Display 0-9
    else
        DispLCD(low - 10 + 'A');     // Display A-F
}

void Hex_data(u32 value)             // Function to display 32-bit hex value
{
    StrLCD("0x");                    // Display prefix

    HexLCD((value>>24)&0xFF);        // Display byte 3
    HexLCD((value>>16)&0xFF);        // Display byte 2
    HexLCD((value>>8)&0xFF);         // Display byte 1
    HexLCD(value&0xFF);              // Display byte 0
}
