#ifndef __USART_H__
#define __USART_H__

void Delay500ms();
void uart_init(unsigned int baud);
void UartSendByte(unsigned char Dat);
void UartSendString(unsigned char *str);

#endif