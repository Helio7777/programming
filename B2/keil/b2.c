#include <reg52.h>
#include "lcd.h"
#include "key.h"
#include "uart.h"
#include "xor.h"
unsigned char calkey(unsigned char *str);
void clear_string_all(char* str, int length);
unsigned char rec_data;
	unsigned char msg[16];
	unsigned char key[16];
	unsigned char ctext[16];
unsigned key1=-1;
void Delay_nms(unsigned int ms);
//void clear_string_all(char* str, int length)；
void main()
{
	unsigned int rec=1,tykey=0;
	unsigned char keynum;
					    P1 = 0xff;
	    uart_init(0xFA); // 9600
    LCD_Init();
		//Delay_nms(50);
		UartSendByte(0);
    while(1)
    {
        keynum = Matrixkey_Scan();
				if(keynum == 13) {LCD_ShowString(0, 1, "TYPE THE KEY");tykey = 1;}
				if(keynum == 15) {rec = 0;}
				if(keynum == 16) {rec = 1;}
				//输入明文
        if(keynum != 0&& rec!=1&&keynum != 15&&tykey!=1&&keynum != 11&&keynum != 12&&keynum != 13&&keynum != 14)
        {
            //LCD_Init();
					LCD_ShowString(0, 1, "Text:");
					if(keynum!=10)
						keynum += '0';
					else
						keynum = '0';
					if(key1!=-1){
					append_char_to_string(keynum, msg);
					LCD_ShowString(0, 7, msg);
						//append_char_to_string(keynum+5,ctext);
            //LCD_ShowString(0, 7, msg);
					UartSendByte(keynum+key1); // 使用发送函数
					Delay_nms(500);
					}else
					{
					LCD_ShowString(0,1,"DO NOT HAVE KEY");
					}
					//P1 = 0xff;
					//LCD_ShowString(1, 1, "PRESSED");
        }
				//输入KEY
				if(keynum != 0&&keynum != 11&&keynum != 12&&keynum != 13&&keynum != 14&&keynum != 15&&keynum != 16&&tykey==1)
				{
					  LCD_ShowString(0, 1, "KEY             ");
					if(keynum!=10)
						keynum += '0';
					else
						keynum = '0';
						append_char_to_string(keynum, key);
						LCD_ShowString(0, 7, key);
					key1=calkey(key);
				}
				//结束输入KEY
				if(keynum != 0&&keynum == 14&&tykey==1)
				{
					tykey=0;
					LCD_ShowString(1,1,"Key:");
					LCD_ShowString(1,5,key);
					LCD_ShowString(0,1,"                ");
				}
				//清除按键
				if(keynum != 0&&keynum == 12)
				{
					clear_string_all(key,16);
					clear_string_all(msg,16);
					clear_string_all(ctext,16);
					key1=-1;
					tykey = 0;
					LCD_ShowString(0,1,"                ");
					LCD_ShowString(1,1,"                ");
					
				}
				
				/*if(keynum != 0&&keynum == 11)
				{
					if(msg[0]!='\0'){
					XOR_EncryptDecrypt(msg,key,StringLength(msg),StringLength(key));
					UartSendString(msg);
				
					}
				}*/
    }
}

void uart() interrupt 4
{
    if (RI)
    {
        rec_data = SBUF;
        RI = 0; // 清除接收中断标志
			if(rec_data != 0){
						rec_data=(rec_data-key1);
						append_char_to_string(rec_data, msg);
            LCD_Init();
            LCD_ShowString(0, 1, "Text:");
            LCD_ShowString(0, 7, msg);
						LCD_ShowString(1,1,"Key:");
					LCD_ShowString(1,5,key);
					//LCD_ShowString(0,1,"                ");
            //LCD_ShowString(1, 1, "PRESSED");
    }
	}
}

void Delay_nms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);
    }
}

void clear_string_all(char* str, int length) {
	int i = 0;
    for (; i < length; i++) {
        str[i] = '\0';
    }
}

unsigned char calkey(unsigned char *str)
{
    unsigned int sum = 0; // 使用unsigned int确保不会溢出
    unsigned char i = 0;

    // 遍历字符串，直到遇到结束符'\0'
    while(str[i] != '\0')
    {
        sum += str[i]; // 将当前字符的ASCII值加到sum
        i++;
    }

    return sum;// % 10; // 对sum取10的余数并返回
}