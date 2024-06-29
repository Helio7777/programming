#include <reg52.h>
#include "xor.h"
void XOR_EncryptDecrypt(unsigned char* data1, unsigned char* key, unsigned int data_length, unsigned int key_length)
{
    unsigned int i;
    for (i = 0; i < data_length; i++)
    {
        data1[i] ^= key[i % key_length];
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

unsigned int StringLength(unsigned char *str)
{
    unsigned int length = 0;

    // 遍历字符串，直到遇到结束符'\0'
    while(str[length] != '\0')
    {
        length++;
    }

    return length;
}