#include "types.h"

void InitLCD(void);
void CmdLCD(u8);
void CharLCD(s8);
void DispLCD(u8);
void StrLCD(s8 *);
void IntLCD(s32);
void FloatLCD(f32,u32);
void WriteToCGRAM(void);
void Hex_data(u32 value);
