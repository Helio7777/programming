#include <reg52.h>
#include "key.h"
#include "delay.h"


unsigned char Matrixkey_Scan(void)
{
	unsigned char temp,row=0,col=0,i=0;
	Matrixkey_Port=0x0f;
	delay_us(1);
	temp=Matrixkey_Port;
	if(temp!=0x0f)
	{
		if(temp==0x0e)row=1;
		else if(temp==0x0d)row=2;
		else if(temp==0x0b)row=3;
		else if(temp==0x07)row=4;
		Matrixkey_Port=0xff;
		delay_us(1);
		Matrixkey_Port=0xf0;
		delay_us(1);
		temp=Matrixkey_Port;
		//if(temp!=0xf0)
			if(temp==0xe0) col=1;
		else if(temp==0xd0)col=2;
		else if(temp==0xb0)col=3;
		else if(temp==0x70)col=4;
			/*switch(temp)
			{
				case 0xe0:col=1;break;
				case 0xd0:col=2;break;
				case 0xb0:col=3;break;
				case 0x70:col=4;break;
				default:break;
			}*/
			while(Matrixkey_Port!=0xf0&&i<255)
			{
				delay_us(1000);
				i++;
			}
		}
		if(row!=0&&col!=0)
				//return 1;
		return ((row-1)*4+col);
		else
			return 0;
}