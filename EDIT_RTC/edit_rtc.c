#include"rtc.h"
#include"lcd.h"
#include"kpm.h"
#include"types.h"
#include"delay.h"
void edit_rtc_info(void)
{
s32  hour,min,sec,date,month,year,day;
u8 choice,key;
u32 num;			
do{
CmdLCD(0x01);
StrLCD((s8*)"1.H 2.M 3.S 4.D");
CmdLCD(0xc0);
StrLCD((s8*)"5.Dt 6.M 7.Y 8.E");
choice=KeyScan();
delayMS(200);
switch(choice)
{
case'1'://HOUR
		   CmdLCD(0x01);
		   StrLCD((s8*)"HOUR(0-23):");
		   ReadNum(&num,&key);
		   if(num>23)
		   {
		     CmdLCD(0x01);
			 StrLCD((s8*)"WRONG INPUT");
			 delayMS(1000);
			}
			else{
			hour=num;
			SetRTCTimeInfo(hour,min,sec);
			}
			delayMS(100);
			break;
case'2'://Minute
		 CmdLCD(0x01);
		 StrLCD((s8*)"Min(0-59):");
		ReadNum(&num,&key);
		 if(num>59)
		 {
		  CmdLCD(0x01);
		  StrLCD((s8*)"WRONG INPUT");
		  delayMS(1000);
		  }
		  else
		  {
		  min=num;
		  SetRTCTimeInfo(hour,min,sec);
		  }
		  break;
case '3'://second
         CmdLCD(0x01);
         StrLCD((s8*)"sec(0-59):");
		 ReadNum(&num,&key);
		 if(num>59)
		 {
		 CmdLCD(0x01);
		 StrLCD((s8*)"wrong input");
		 delayMS(1000);
		 }
		 else
		 {
		 SetRTCTimeInfo(hour,min,sec);
		 }
		 break;
case '4'://day
         CmdLCD(0x01);
		 StrLCD((s8*)"day(0-6):");
		 ReadNum(&num,&key);
		 if(num>6)
		 {
		  CmdLCD(0x01);
		  StrLCD((s8*)"wrong input");
		  delayMS(1000);
		  }
		  else
		  {
		  day=num;
		  SetRTCDay(day);
		  }
		  break;
case '5'://Date
         CmdLCD(0x01);
		 StrLCD((s8*)"Date(1-31):");
		 ReadNum(&num,&key);
		 if(num<1 || num>31)
		 {
		 CmdLCD(0x01);
		 StrLCD((s8*)"wrong input:");
		 delayMS(1000);
		 }
		 else{
		 date=num;
		 SetRTCDateInfo(date,month,year);
		 }
		 break;
case '6'://Month
         CmdLCD(0x01);
		 StrLCD((s8*)"month(1-12):");
		 ReadNum(&num,&key);		 
		 if(num <1 || num>12)
		 {
		 CmdLCD(0x01);
		 StrLCD((s8*)"wrong input");
		 delayMS(1000);
		 }
		 else{
		 month=num;
		 SetRTCDateInfo(date,month,year);
		 }
		 break;
case '7'://year
         CmdLCD(0x01);
		 StrLCD((s8*)"Enter Year:");
		   ReadNum(&num,&key);
		   year=num;
		  SetRTCDateInfo(date,month,year);
		  break;
case'8'://exit
        CmdLCD(0x01);
		break;
		}
		}while(choice!='8');
}