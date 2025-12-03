#include<LPC214X.h>
#include"types.h"
#include"pin_connect_block.h"
#include"pin_function_defines.h"
#include"adc_defines.h"
#include"delay.h"
void Init_ADC(void){
//cfg ADCR SFR
AD0CR=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BIT);
//cfg p0.27 pin as analog input pin0(AIN0)
cfgPortPinFunc(0,28,PIN_FUNC2);
}
void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR)
{
//clear any previous channel selection
	AD0CR&=0xFFFFFF00;

	//update req channel select,

	//start analog samping & conversion

	AD0CR|=1<<chNo|1<<ADC_START_BIT;

	delayUS(3);

	while(((AD0GDR>>DONE_BIT)&1)==0);

	AD0CR&=~(1<<ADC_START_BIT);

	*adcDVal=(AD0GDR>>RESULT_BITS)&1023;

	*eAR = (*adcDVal * (3.3/1023));

}
