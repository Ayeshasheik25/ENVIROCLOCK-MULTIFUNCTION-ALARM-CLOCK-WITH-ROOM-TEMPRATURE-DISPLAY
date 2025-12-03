#include<LPC214X.h>				 
#include"adc.h"
#include"lcd.h"
#include"kpm.h"
#include"rtc.h"
#include"types.h"
#include"delay.h"
#include"alarm.h"
#include"lcd_defines.h"
#include"pin_function_defines.h"
#include"pin_connect_block.h"
#include"rtc_defines.h"
#define BUZZER_PIN 25 
s32  hour,min,sec,date,month,year,day;
u8 alarm_hour=0,alarm_min=0;
u8 extint_flag=0;
u32 adcVal;
f32 vol,temp;
void eint0_isr(void)__irq
{
u8 choice;
extint_flag=1;
do{
 CmdLCD(0x01);
 StrLCD((s8*)"1.Edit RTC");
 CmdLCD(0xc0);
 StrLCD((s8*)"2.Alarm 3.Exit");
 choice=KeyScan();
 delayS(1);
switch(choice)
{ 
 case'1':edit_rtc_info();
          break;
  case '2':set_alarm();
           break;
}
}while(choice!='3');
CmdLCD(0x01);
EXTINT=1<<0;
VICVectAddr=0;
}
void extint_init(void){
cfgPortPinFunc(0,1,EINT0_0_1);
VICIntEnable=1<<14;
VICVectCntl0=(1<<5)|14;
VICVectAddr0=(u32)eint0_isr;
EXTMODE=1<<0;
EXTPOLAR=0;
}
int main()
{
Init_LCD();
Init_KPM();
Init_ADC();
RTC_Init();
extint_init();
SetRTCTimeInfo(15,25,0);
SetRTCDateInfo(30,10,2025);
SetRTCDay(3);
IODIR0|=(1<<BUZZER_PIN);
IOCLR0=(1<<BUZZER_PIN);

while(1)
{
GetRTCTimeInfo(&hour,&min,&sec);
GetRTCDateInfo(&date,&month,&year);
GetRTCDay(&day);
CmdLCD(0x80);
DisplayRTCTime(hour,min,sec);
DisplayRTCDay(day);

CmdLCD(0xc0);
DisplayRTCDate(date,month,year);
Read_ADC(1,&adcVal,&vol);
temp=vol*100;
CmdLCD(0xc0 +11);
StrLCD((s8*)"T:");
F32LCD(temp,1);
CharLCD(0xDF);
CharLCD('C');
check_alarm();

if(extint_flag)
{
extint_flag=0;
}
}
}