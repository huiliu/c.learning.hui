/*
 * 此文件用于演示多维数组名的指针作用特点
 * 
 * 2012-06-16 17:47:44
 * Date: Sat Jun 16 18:06:18 CST 2012
 */

#include <stdio.h>

int main(int argc, char **argv)
{

    int A[2][2] = {{1,2},{3,4}};
    int *p;
    // 会引起错误
    //int **pr;
    int (*pr)[2];
    pr = A;
    // 多维数组到一维数组的映射
    // A[d1][d2][d3]
    // p = A
    // A[i][j][k] = p + i * d2 * d3 + j *d3 + k
    p = (int *)A;
    
    printf("A     = \t%p\n", A);
    printf("&A[0] = \t%p\n", &A[0]);
    printf("A[0]  = \t%p\n", A[0]);
    printf("&A[0][0] = \t%p\n\n", &A[0][0]);

    printf("*A    = \t%p\n", *A);
    printf("*A+1    = \t%p\n", *A+1);
    printf("*pr+1   = \t%p\n", *pr+1);
    printf("A[0]+1  = \t%p\n", A[0]+1);
    printf("*(*A+1)    = \t%d\n", *(*A+1));
    printf("**A   = \t%d\n\n", **A);

    printf("A+1     = \t%p\n", A+1);
    printf("*(A+1)     = \t%p\n", *(A+1));
    printf("**(A+1)     = \t%d\n", **(A+1));
    printf("*(A+1)+1     = \t%p\n", *(A+1)+1);
    printf("*(*(A+1)+1)     = \t%d\n\n", *(*(A+1)+1));
    // 从上面看，数组名应该是一个二级指针，但是如果将其赋给另一个二级
    // 指针则会发生错误....

    printf("pr    = \t%p\n", pr);
    printf("*pr   = \t%p\n", *pr);
    printf("**pr   = \t%d\n", **pr);

    printf("\np = %p\n", p);
    printf("*p = %d\n", *p);
    printf("*(p+1) = %d\n", *(p+1));
    printf("*(p+2) = %d\n", *(p+2));
    printf("*(p+3) = %d\n", *(p+3));
    return 0;
}

/*
    int x[m][n];

    int **pr = x;   //错误

 ------------------------------>(*x)++
 |       x
 |        \  [0]   [1]   [2] 
 |         \ ---   ---   ---
 |  x[0] -->|   | |   | |   | ......
 |           ---   ---   ---
 |           ---   ---   ---
 |  x[1] -->|   | |   | |   | ......
 |           ---   ---   ---
 |           ---   ---   ---
 |  x[2] -->|   | |   | |   | ......
 |           ---   ---   ---
 |   .
 |   .
 x++ .

 */
