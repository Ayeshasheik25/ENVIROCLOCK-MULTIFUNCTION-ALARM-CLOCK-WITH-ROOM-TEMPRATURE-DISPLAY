//clock defines
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADCCLK 3000000 //<=4.5MHZ
#define CLKDIV ((PCLK/ADCCLK)-1)

//ADCR SFR defines
#define CLKDIV_BIT 8
#define ADC_START_BIT 24
#define PDN_BIT 21

//ADDR SFR defines
#define RESULT_BITS 6
#define DONE_BIT 31
