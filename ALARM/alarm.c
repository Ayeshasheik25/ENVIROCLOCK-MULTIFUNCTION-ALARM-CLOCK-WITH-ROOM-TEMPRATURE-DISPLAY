#include<LPC21XX.h>
#include"types.h"
#include"lcd.h"
#include"kpm.h"
#include"rtc.h"
#include"delay.h"
#include"alarm.h"
#include"lcd.h"
#include "lcd_defines.h"
#define BUZZER_PIN 25
u8 alarm_h=0,alarm_m=0;
 u8 alarm_on=0;
extern u8 bell_symbol[8]=
{
0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00
};
void set_alarm(void)
{ 
 u8 key;
 u32 hh,mm;
 CmdLCD(0x01);
 StrLCD((s8*)"HH:MM");
 CmdLCD(0xc0);
  ReadNum(&hh,&key);
  delayS(1);
 if(hh>23)
 {
 CmdLCD(0x01);
 StrLCD((s8*)"wrong input");
 delayMS(1000);
 return;
 }
 CharLCD(':');
 ReadNum(&mm,&key);
 delayS(1);
 if(mm>59)
 {
 CmdLCD(0x01);
 StrLCD("wrong input");
 delayMS(1000);
 return;
 }
 alarm_h=hh;
 alarm_m=mm;
 CmdLCD(0x01);
 CmdLCD(0xc0);
 U32LCD(alarm_h);
 CharLCD(':');
 U32LCD(alarm_m);
 delayMS(1000);
 StrLCD((s8*)"Alarm set:");
 }
 void check_alarm(void)
 {
 s32  hour,min,sec;

 GetRTCTimeInfo(&hour,&min,&sec);
   if(hour==alarm_h&&min==alarm_m&&alarm_on==0)
   {
   BuildCGRAM(bell_symbol,8);
    CmdLCD(0x80+15);
   CharLCD(' ');
   alarm_on=1;
  while(1)
  {
  if((IOPIN1&(1<<29))==0)
  {
  IOCLR0=1<<BUZZER_PIN;
  //delayS(2);
  //alarm_on=0;
  return;
  //break;
  }
  else
  {
  IOSET0=(1<<BUZZER_PIN);
  delayMS(300);
  IOCLR0=(1<<BUZZER_PIN);
  delayMS(300);
  }
  }
  }
  GetRTCTimeInfo(&hour,&min,&sec);
  if(min!=alarm_m)
  {
  alarm_on=0;
  return;
  }


}