#include <arpa/inet.h>
#include <stdio.h>

int main()
{
    unsigned char buf[4] = {192, 168, 1, 2};
    int num = *(int*)buf; // 取出buf中的4个字节
    int sum = htonl(num); // 将num转换为大端的网络字节序
    unsigned char *p = &sum; // 将sum转换为无符号字符指针
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3)); // 2.1.168.192

    unsigned short a = 0x0102;
    unsigned short b = htons(a); 
    printf("%x\n", b); // 201

    return 0;
}