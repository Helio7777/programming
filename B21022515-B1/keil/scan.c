#include <reg52.h>
#include "scan.h"
#include "delay.h"
// Define your key mapping here. This is just an example.
#define KeyPort P1

// 声明函数
void delay(unsigned int time);
unsigned char KeyScan();

// 延时函数
void delay(int z)  
{
	int x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}

unsigned char key_scan()
{
	char value_h,value_l;
	unsigned char key;
	P1 = 0xF0;
	if(P1 != 0xF0){
		P1 = 0xF0;
		value_l = P1;
		delay(10); //按键消抖
		P1 = 0x0F;
		delay(10);
		value_h = P1;
		
		key = value_l+value_h; //得到键值
	}
	P1 = 0xF0;
	
	//key_press = 1;
	return key;
}