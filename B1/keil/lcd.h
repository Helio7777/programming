#ifndef _LCD_H_
#define _LCD_H_

void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Init(void);
void LCD_SetCursor(unsigned char Line,unsigned char Columu);
void LCD_Showchar(unsigned char Line,unsigned char Columu,unsigned char Char);
void LCD_ShowString(unsigned char Line,unsigned char Columu,unsigned char *String);

#endif