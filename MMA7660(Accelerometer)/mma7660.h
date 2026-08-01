#include "types.h"

void Init_mma7660(void);
u8 mma7660_read(u8 reg);
void mma7660_write(u8 reg, u8 data);
s8 mma7660_get_x(void);
s8 mma7660_get_y(void);
s8 mma7660_get_z(void);

