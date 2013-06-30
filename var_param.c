// -------------------------------------------------
//
// 此文件用来研究演示如何在函数中使用数目可变的形参
//
// -------------------------------------------------

#include <stdio.h>
// 包含处理变长参数表的宏
#include <stdarg.h>

int maxv(int , ...);

int main(int argc, char **argv)
{
    printf("Max = %d\n", maxv(5, 2, 5, 4, 6, 8));
    return 0;
}

int maxv(int a, ...)
{
    int max_v, next;
    int i;
    // Step 1.  定义一个va_list类型数据用于存储首个可变变量地址
    va_list arg_addr;

    // Step 2.  利用宏va_start取得首个可变变量地址
    //  va_start()有两个参数，第一个为va_list类型，用于存储可变变量
    //  地址；第二个为最后一个有名变量的变量名
    va_start(arg_addr, a);

    for (i = 0; i < a; i++){
        // Step 3.  用宏va_arg取得va_list中的值。
        //  va_arg()有两个参数，第一个为va_list类型，存储着可变变量
        //  地址第二个为变量的数据类型
        //  读取当前地址中的值之后，va_arg会将地址移到下一个变量的地址
        //  注意：char, short会被转为int；float会被转为double
        //      一个要通过某种方式来确定可变变量的数目，否则出错
        if ((next = va_arg(arg_addr, int)) > max_v);
            max_v = next;
    }
    // Step 4.  进行清理
    va_end(arg_addr);
    return max_v;
}
