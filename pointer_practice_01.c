/*
 *  此代码包含一些指针操作的示例：
 *      1. 指向一维，二维数组的指针
 *      2. 指向函数的指针
 *      3. 利用指针倒转字符串
 */


#include <stdio.h>
#include <string.h>

void visit_array_by_pointer(void);
void revers_string(void);
int func(char *pr);
void p2func(void);

int main(int argc, char **argv)
{
    //visit_array_by_pointer();    
    //revers_string();
    p2func();
    return 0;
}

void visit_array_by_pointer(void)
{
    // 一级指针
    int A[3] = {1, 2, 3};
    int *p;
    int i, j = 0;

    p = A;
    for (i = 0; i < 3; i++){
        printf("%d\t", *(p + i + j));
        printf("\n");
    }

    // 二级指针
    int B[3][3] ={
                    {1, 2, 3},
                    {2, 3, 2},
                    {3, 4, 9}
              };

    // 指向多维数组的指针
    int (*pp)[3];
    pp = B;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
          printf("%d\t", *(*(pp + i) + j));
        }
        printf("\n");
    }
}

void revers_string(void)
{
    char text[10], *p;
    int i, count = 10;

    p = text;

    for (i = 0; i < count; i++){
        *p = getchar();
        p++;
    }

    for (i = 0; i < count; i++){
        p--;
        printf("%c", *p);
    }
}

int func(char *pr)
{
    printf("%s\n", pr);
    return 0;
}

void p2func(void)
{
    // 指向函数的指针
    int (*p)(char *);
    int i;
    p = func;
    
    i = p("hello World, Function pointer!");
    printf("%d\n", i);
}
