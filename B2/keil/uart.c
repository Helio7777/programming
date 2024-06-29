#include <reg52.h>
#include "delay.h"
void uart_init(unsigned int baud)
{
    //TMOD &= 0x0F;  // 清除TMOD中定时器1的高4位
    TMOD |= 0x20;  // 设置定时器1为模式2（8位自动重装）

    SCON = 0x50;   // 设置串口模式1（8位数据，1停止位，无校验）
    
    PCON |= 0x80;  // 设置波特率倍增位（SMOD位）

    TH1 = baud;    // 设置定时器1高位
    TL1 = baud;    // 设置定时器1低位

    ES = 1;        // 使能串口中断
    EA = 1;        // 使能总中断
    TR1 = 1;       // 启动定时器1
}

void UartSendByte(unsigned char Dat)
{
    unsigned int timeout = 10000; // 超时计数器，值可以根据需要调整

    SBUF = Dat;

    while(TI == 0&&timeout>0)
    {
        timeout--;
    }

    TI = 0;
}

void UartSendString(unsigned char *str)
{
	while(*str != '\0')
	{UartSendByte(*str);
		str++;
	}
}