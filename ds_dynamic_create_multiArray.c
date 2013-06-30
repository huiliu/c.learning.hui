#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,n) \
    if (!(p = malloc(n))) { \
        printf("内存分配错误\n");\
        exit(EXIT_FAILURE);\
    }

#define CALLOC(p,n,s) \
    if (!(p = calloc(n, s))) { \
        printf("内存分配错误\n"); \
        exit(EXIT_FAILURE); \
    }

void *create_multi_array(int row, int col);

int main(int argc, char **argv)
{
    int **multi_array;
    multi_array = create_multi_array(2, 2);
    printf("%d\n", *(*multi_array));
    return 0;
}

// 动态分配一个二维数组
void *create_multi_array(int row, int col)
{
    // 指针与多维数组的关系需要深入了解
    int **pr;
    int i;

    // 用宏真是方便啊
    CALLOC(pr, row, sizeof(int));
    //if ((pr = calloc(row, sizeof(int))) == NULL)
    //    return NULL; 
    for (i = 0; i < row; i++){
        CALLOC(pr[i], col, sizeof(int));
        //if ((pr[i] = calloc(col, sizeof(int))) == NULL)
        //    return NULL;
        pr++;
    }
    **pr = 100;
    return pr;
}
