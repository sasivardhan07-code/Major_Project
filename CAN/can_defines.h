#include "types.h"

#define RD1_PIN_0_25 0x15440000 //PIN_FUN2

#define PCLK 15000000
#define BIT_RATE 125000
#define QUANTA 15
#define BRP (PCLK/(BIT_RATE*QUANTA))
#define SAMPLE_POINT (0.7*QUANTA)
#define TSEG1 ((u32)SAMPLE_POINT-1)
#define TSEG2 (QUANTA-(1+TSEG1))
#define SJW ((TSEG2 >= 5)?4:(TSEG2-1))

#define SAM 0
#define BTR_LVAL ((SAM<<23)|((TSEG2-1)<<20)|((TSEG1-1)<<16)|((SJW-1)<<14)|(BRP-1))

#define TR_BIT 0
#define RRB_BIT 2 
#define STB1_BIT 5

#define RBS_BIT 0
#define TBS1_BIT 2
#define TCS1_BIT 3

#define FF_BIT 31
#define RTR_BIT 30
#define DLC_BIT 16

#define RM_BIT 0

#define AccOFF_BIT 0
#define AccBP_BIT 1
