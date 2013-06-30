/*
 * 此文件主要用于演示用二级指针完成数组操作（矩阵操作）
 * 用于熟悉矩阵与数组之间的关系
 *
 * 存在问题：
 *      当DEMENSION大于等于5时，会发生错误
 *
 * Date: Sat Jun 16 21:43:06 CST 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MALLOC(p,n) \
    if (!(p = malloc(n))) { \
        printf("内存分配错误！\n");\
        exit(EXIT_FAILURE);\
    }

#define CALLOC(p,n,s) \
    if (!(p = calloc(n, s))) { \
        printf("内存分配错误！\n");\
        exit(EXIT_FAILURE);\
    }

#define DIMENSION   4

//#define DEBUG

void initMatrix(int **a, int rows, int cols, int range);
void **mk2dMatrix(int rows, int cols);
int** m_add(int **a, int **b, int **c, int row, int col);
void m_output(int** a, int m, int n);
int** m_mult(int **a, int **b, int **c, int n);
void m_transpose(int **a, int rows);
int** m_transposeX(int **a, int **b, int rows, int cols);

int main(int argc, char** argv)
{
    int **A, **B, **C, **D;

    A = (int **)mk2dMatrix(DIMENSION, DIMENSION);
    B = (int **)mk2dMatrix(DIMENSION, DIMENSION);
    C = (int **)mk2dMatrix(DIMENSION, DIMENSION);
    D = (int **)mk2dMatrix(DIMENSION, DIMENSION);

    initMatrix(A, DIMENSION, DIMENSION, 21);
    initMatrix(B, DIMENSION, DIMENSION, 20);
    m_output(A, DIMENSION, DIMENSION);
    m_output(B, DIMENSION, DIMENSION);

    m_add(A, B, C, DIMENSION, DIMENSION);
    m_output(C, DIMENSION, DIMENSION);

    m_mult(A, B, D, DIMENSION);
    m_output(D, DIMENSION, DIMENSION);

    m_transpose(A, DIMENSION);
    m_output(A, DIMENSION, DIMENSION);

    int **AA, **BB;
    AA = (int **)mk2dMatrix(3, 4);
    initMatrix(AA, 3, 4, 9);
    BB = (int **)mk2dMatrix(4, 3);

    m_transposeX(AA, BB, 3, 4);
    m_output(AA, 3, 4);
    m_output(BB, 4, 3);

    return 0;
}

void **mk2dMatrix(int rows, int cols)
{
    int **m, i, j;

    CALLOC(m, rows, sizeof(int));

    for (i = 0; i < rows; i++){
        CALLOC(m[i], cols, sizeof(int));
        for (j = 0; j < rows; j++)
            m[i][j] = 0;
    }
    return (void **)m;
}
void initMatrix(int **a, int rows, int cols, int range)
{
    int i, j;

    // 用于产生随机数的种子
    srand(time(NULL));
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            //产生随机数
            a[i][j] =  rand() % range;
}

int** m_add(int **a, int **b, int **c, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            *(*(c + i) + j) = *(*(a + i) + j) + *(*(b + i) + j);
        }
    }
    return c;
}

int** m_mult(int **a, int **b, int **c, int n)
{
    int i, j, k;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            *(*(c + i) + j) = 0;
            for (k = 0; k < n; k++)
                //*(*(c + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
                c[i][j] += a[i][k] * b [k][j];
        }
    }
    return c;
}

// 转置方阵
void m_transpose(int **a, int rows)
{
    int i, j, tmp;
    for (i = 0; i < rows; i++){
        for (j = i + 1; j < rows; j++){
            #ifdef DEBUG
            printf("交换前:\n");
            printf("i = %d\tj = %d\t%d\n", i, j, a[i][j]);
            printf("j = %d\ti = %d\t%d\n", j, i, a[j][i]);
            #endif
            tmp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = tmp;
            #ifdef DEBUG
            printf("交换后:\n");
            printf("i = %d\tj = %d\t%d\n", i, j, a[i][j]);
            printf("j = %d\ti = %d\t%d\n", j, i, a[j][i]);
            #endif
        }
    }
}

// 转置任意矩阵
// a    为输入矩阵
// b    为输入矩阵
int** m_transposeX(int **a, int **b, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            b[j][i] = a[i][j];
        }
    }
    return b;
}

void m_output(int** a, int m, int n)
{
    static int x = 0;
    printf("第%d个矩阵为:\n", x++);
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++)
            printf("%d\t", *(*(a+i)+j));
        printf("\n");
    }
}

