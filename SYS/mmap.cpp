#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

/*
    内存映射：
    优点:   
    1.对文件的读取操作跨过了页缓存，减少了数据的拷贝次数，用内存读写取代I/O读写，提高了文件读取效率。减少read、write系统调用。
    2.提供进程间共享内存及相互通信的方式。

    缺点：
    1.文件太小，也会占用整个页（一般为4KB），造成内存浪费。
    2.创建、销毁、缺页造成的开销很大。
*/

#define GiB *(1024LL * 1024 * 1024)

void test1() // 匿名映射
{
    void *p = mmap(NULL, 3 GiB, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if(p == MAP_FAILED) {
        printf("mmap failed!\n");
    }else{
        printf("mmap success!\n");
    }
    
    *(int *)((u_int8_t*)p + 1 GiB) = 114;
    *(int *)((u_int8_t*)p + 2 GiB) = 115;

    printf("read = %d\n", *(int *)((u_int8_t*)p + 2 GiB));
}

void test2() // 共享映射
{
    // 把磁盘文件放入共享内存，这样可以使用指针访问磁盘文件 mytest.txt必须有内容。
    int fd = open("mytest.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open error!");
        exit(1);
    }
    //申请共享映射
    void *p = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap error!");
        exit(1);
    }
    printf("%s\n", (char *)p); // 打印mytest.txt文件内容

    // 向mytest.txt文件添加"abc"
    strcpy((char *)p + 1, "abc");

    int ret = munmap(p, 100); //释放共享映射
    if (ret == -1)
    {
        perror("munmap error!");
        exit(1);
    }
    close(fd);
}

int main()
{
    test1();
    test2();
}
