#include <reg52.h>
#include "delay.h"
/*It genarates a approximate delay of 10us for each count,
if 5000 is passed as the argument then it generates a delay of apprx 50ms.*/
void delay_us(unsigned int us_count)
{
	while(us_count!=0)
	{
		us_count--;
	}
}

/*It genarates a approximate delay of 1ms for each count, 
if 1000 is passed as the argument then it generates delay of apprx 1000ms(1sec)*/
void delay_ms(unsigned int l)
{
   unsigned char i,j;	
	 for(i=0;i<(10*l);i++)
	  for(j=0;j<33;j++)
	   ;		 
 }

/*It genarates a approximate delay of 1sec for each count,
if 10 is passed as the argument then it generates delay of apprx 10sec
note: A max of 255 sec delay can be generated using this function.*/
/*void delay_sec(unsigned char sec_count)
{
	while(sec_count!=0)
	{
		delay_ms(1000); //delay_ms is called to generate 1sec delay 
		sec_count--;
	}
}*/