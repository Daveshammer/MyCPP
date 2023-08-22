#include <stdio.h>

#include <arpa/inet.h>

int main()
{
    char buf[] = "192.168.1.4";
    unsigned int num = 0;
    inet_pton(AF_INET, buf, &num); // 将字符数组转换为网络字节序的整数
    unsigned char *p = (unsigned char *)&num;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3)); // 192 168 1 4

    char ip[16] = "";
    inet_ntop(AF_INET, &num, ip, 16); // 将网络字节序的整数转换为字符数组
    printf("%s\n", inet_ntop(AF_INET, &num, ip, 16)); // 192.168.1.4

    return 0;
}