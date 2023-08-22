#include <arpa/inet.h>
#include <stdio.h>

int main()
{
    unsigned char buf[4] = {2, 1, 168, 192};
    int num = *(int*)buf; // 取出buf中的4个字节
    int sum = ntohl(num); // 将num转换为主机字节序
    unsigned char *p = (unsigned char*)&sum; // 将sum转换为无符号字符指针
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3)); // 192.168.1.2

    unsigned short a = 0x0201;
    unsigned short b = ntohs(a); 
    printf("%x\n", b); // 102

    return 0;
}
