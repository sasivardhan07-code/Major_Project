 #define FOSC 12000000
 
 #define CCLK (FOSC*5)

 #define PCLK1 (CCLK/4)

 #define ADCCLK 3000000
 #define CLKDIV ((PCLK1/ADCCLK)-1)

 #define CLKDIV_BITS_START 8
 #define PDN_BIT 21
 #define CONV_START_BIT 24

 #define RESULT_BITS_START 6
 #define DONE_BIT 31

 #define AIN0_0_27  0x00400000
 #define AIN1_0_28	0x01000000
 #define AIN2_0_29	0x04000000
 #define AIN3_0_30	0x10000000
