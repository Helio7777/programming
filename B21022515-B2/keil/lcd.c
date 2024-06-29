#include <regx52.h>
#include "lcd.h"
#include "delay.h"
#define LCD_DataPort P0
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_E = P2^2;

void LCD_Delay1ms(int z)//延时函数
{
	delay_us(z*1000);
}

void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_E = 1;
	LCD_Delay1ms(1);
	LCD_E = 0;
	LCD_Delay1ms(1);
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_E = 1;
	LCD_Delay1ms(1);
	LCD_E = 0;
	LCD_Delay1ms(1);
}
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0c);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}
void LCD_SetCursor(unsigned char Line,unsigned char Columu)
{
	if(Line == 1){
		LCD_WriteCommand(0x80 | (Columu - 1));
	}
	else{
		LCD_WriteCommand((0x80 | Columu - 1) + 0x40);
	}
}
void LCD_Showchar(unsigned char Line,unsigned char Columu,unsigned char Char)
{
	LCD_SetCursor(Line,Columu);
	LCD_WriteData(Char);
}
void LCD_ShowString(unsigned char Line,unsigned char Columu,unsigned char *String)
{
	unsigned char i;
	unsigned char* error = "OUT OF LENGTH";
	/*if(String[16]!='\0')
	{
			LCD_SetCursor(Line,Columu);
	for(i=0;error[i]!='\0';i++)
		LCD_WriteData(error[i]);
	}else*/{
	LCD_SetCursor(Line,Columu);
	for(i=0;String[i]!='\0';i++)
		LCD_WriteData(String[i]);

	}
}