#include <reg52.h>
#include "lcd.h"
#include "key.h"
#include "cal.h"

char keyMap[16] = {'7', '8', '9', '/', '4', '5', '6', 'X', '1', '2', '3', '-', 'C', '0', '=', '+'};

void main()
{
	unsigned char result;
	P1=0xff;
	LCD_Init();
	//LCD_ShowString(1,2,"abc");
    while(1) {
        result = Matrixkey_Scan();
        if (result != 0) {
					//LCD_ShowString(0,1,"abc");
				Calculator(keyMap[(result-1)]);
        }
    }

}