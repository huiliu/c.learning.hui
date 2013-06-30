/*
 * 此文件主要用于演示变量的作用范围，嵌套块时，块内变量不块外变量无关
 *
 */

#include <stdio.h>

int var1 = 5;

int main(int argc, char **argv)
{
    var1++;
    printf("Super: %d\n", var1);
    int var1 = 100;
    var1 += 50;

    printf("Block1: %d\n", var1);

    {
        int var1 = 10;
        var1 += 10;
        printf("Block2: %d\n", var1);
    }

    {
        int var1 = 50;
        var1 += 10;
        printf("Block2: %d\n", var1);
    }

    printf("Summary:\n局部变量与非此局部变量重名，互不干扰\n");

    return 0;
}
