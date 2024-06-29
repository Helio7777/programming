#include <reg52.h>  // 包含51单片机的头文件
#include <stdio.h>  // 包含标准输入输出库

#include "lcd.h"

#define uchar unsigned char
#define uint unsigned int


// 用于存储操作数和操作符
long num1 = 0, num2 = 0;
char operation = 0;
uchar buffer[16];
//char temp = '\0'; 
	
void append_char_to_string(char c, char* str);
void Clear_line(int n)
{
	LCD_ShowString(n,1,"                ");
}
// 显示在LCD上的函数
void DisplayResult(long result) {
    sprintf(buffer, "%ld", result);
    LCD_ShowString(0, 1, buffer);
}

void append_string_to_string(char* str1, char* str2) {
		int i=0;
    while(str2[i] != '\0') {
        append_char_to_string(str2[i], str1);
        i++;
    }
}

void append_char_to_string(char c, char* str) {
    int len = 0;

    // Find the current end of the string
    while(str[len] != '\0') {
        len++;
    }

    // Add the new character to the end of the string
    str[len] = c;

    // Null terminate the new string
    str[len+1] = '\0';
}

void clear_string_all(char* str, int length) {
	int i = 0;
    for (; i < length; i++) {
        str[i] = '\0';
    }
}

void ConvertToBase(long number, int base, char *result) {
    char digits[] = "0123456789ABCDEF";
    int i = 0, j;
    char temp;

    // 特殊情况：如果数字为0
    if (number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    // 转换过程
    while (number > 0) {
        result[i++] = digits[number % base];
        number /= base;
    }
    result[i] = '\0';

    // 反转字符串
    for (j = 0; j < i / 2; j++) {
        temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}


// 计算器功能函数，接受按键值keynum
void Calculator(char keynum) {
    static long result = 0;
    static uchar is_result_displayed = 0;
		static char f[16] = "\0";
		int nn = 0;
		append_char_to_string(keynum, f);
		LCD_ShowString(1,1,f);
    // 如果是数字键
    if (keynum >= '0' && keynum <= '9') {
        if (is_result_displayed) {
            num1 = 0;
            is_result_displayed = 0;
        }
        num1 = num1 * 10 + (keynum - '0');
        sprintf(buffer, "%ld", num1);
        //LCD_ShowString(0, 1, buffer);
    } 
    // 如果是操作符
    else if (keynum == '+' || keynum == '-' || keynum == 'X' || keynum == '/') {
			        //sprintf(buffer, "%ld", num1);
        //LCD_ShowString(1, 1, buffer);
        operation = keynum;
        num2 = num1;
        num1 = 0;
			//Clear_line(0);
    } 
    // 如果是等号键
    else if (keynum == '=') {
        switch (operation) {
            case '+':
                result = num2 + num1;
                break;
            case '-':
                result = num2 - num1;
                break;
            case 'X':
                result = num2 * num1;
                break;
            case '/':
                if (num1 != 0) {
                    result = num2 / num1;
										nn = num2*10/num1;
										nn = nn%10;
                } else {
                    LCD_ShowString(0, 1, "Error           ");
                    return;
                }
                break;
						case 0:
							if(num1==0)
								{
									LCD_ShowString(0,1,"B21022515");
									Clear_line(1);
									LCD_ShowString(1,1,"0");
									clear_string_all(f,16);
								}
							if(num2==0){
								num2=num1;
						    num1=0;
								return;
							}if(num1!=0&&num2!=0){
							ConvertToBase(num2,num1,buffer);
							append_string_to_string(f, buffer);
							LCD_ShowString(1,1,f);
							is_result_displayed = 0;
							num1 = result;
							num2 = 0;
								return;
							}	
						break;
            default:
                //LCD_ShowString(0, 1, "No Op");
                return;
        }
								//Clear_line(0);
								//Clear_line(1);
        //DisplayResult(result);
				sprintf(buffer,"%ld",result);
				append_string_to_string(f, buffer);
				if(nn!=0){
				sprintf(buffer,".%d",nn);
				append_string_to_string(f, buffer);
				}
				if(f[16]!='\0')
				{
					Clear_line(0);
					LCD_ShowString(0,1,"ERROR!");
				}
				//LCD_ShowString(0,1,buffer);
				LCD_ShowString(1,1,f);
        is_result_displayed = 0;
        num1 = result;
        num2 = 0;
				operation=0;

    } 
    // 如果是归零键
    else if (keynum == 'C') {
        num1 = 0;
        num2 = 0;
        operation = 0;
				clear_string_all(f,16);
				LCD_Init();
        LCD_ShowString(1, 1, "0");
    }
}