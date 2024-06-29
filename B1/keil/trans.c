#include <reg52.h>
char original[] = {0xf0,0x};
// 目标字符组
char target[] = "bcdef";

/*// 映射函数
unsigned char somef(char ch) {
    for (int i = 0; i < sizeof(original); i++) {
        if (ch == original[i]) {
            return target[i];
        }
    }
    return ch;  // 如果字符不在原字符组中，返回原字符
}*/