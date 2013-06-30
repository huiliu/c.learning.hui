/*
 * 此文件主要实现了，高斯消元法，将矩阵转换为上三角阵
 *
 * Date: Thu Jun 28 01:55:54 CST 2012
 *
 * UPDATE:
 *      从文件中读取矩阵元
 *
 * Rivise Date: Thu Jun 28 02:37:39 CST 2012
 *
 * BUG:
 *      如果输入的矩阵为100阶，且矩阵元为1－10000按序排列，会出现错误
 *      但是，若将数字顺序打乱，则不会出错。
 *      应该是程序某个地方边界检查不够.
 *  
 * UPDATE Date:       Thu Jun 28 03:28:14 CST 2012
 *
 * UPDATE:
 *      1. 修复上面提到BUG，产生原因为判断方阵为奇异的条件不正确
 *      2. 完成程序，可以完整的解线性方程，采用列选主元高斯消元
 *
 * UPDATE Date: Thu Jun 28 11:11:01 CST 2012
 *
 * UPDATE:
 *      1. 增加新的函数，利用高斯消元法，求解矩阵的逆阵
 *      2. 修改eliminate函数，将输入矩阵拷贝一个副本，以免干扰数值
 *
 * UPDATE Date: Thu Jun 28 19:29:29 CST 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#define DEBUG 
//#define DEBUG_FILE

// 进行高斯消元
double** eliminate(const double **M, int m, int n);
// 输出矩阵元
void output_A(double **A, int m, int n);
// 从文件中读取数据
double **readMatrix(const char *file_name, int *m, int flags);
// 解线性方程
double** solve(double **M, int n);
// 求解逆阵
double **invers(double **M, double **MI, int n);
// 得到一个n阶的单位矩阵
double **matrix_I(int n);
// 将矩阵转置
void revers(double **M, int row, int col);
// 矩阵乘法
double** multi(double **A, double** B, int n);

int main(int argc, char **argv)
{

    int n;
    double **pFile, **e, **s;

    if (argc == 1) {
        printf("Please enter the file name which contain Matrix data!\n\nUsage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pFile = readMatrix(argv[1], &n, 1);
#ifdef DEBUG
    output_A(pFile, n, n);
#endif
    e = eliminate((const double **)pFile, n, n+1);
    if (!e)
        exit(EXIT_FAILURE);

    printf("RESULT...\n");
    output_A(e, n, n+1);

    s = solve(e, n);
    printf("方程的解为:\n");
    output_A(s, 1, n);

    // 求逆阵
    double **T = readMatrix("gauss_inverse", &n, 0);
    double **M_I = matrix_I(n);

    output_A(T, n, n);
#ifdef DEBUG_INVERSE
    printf("输出单位矩阵:\n");
    output_A(M_I, n, n);
#endif
    double **II = invers(T, M_I, n);
    revers(II, n, n);
    printf("输出逆阵:\n");
    output_A(II, n, n);
    printf("测试:\n");
    output_A(multi(T, II, n), n, n);

    return 0;
}

double** eliminate(const double **M, int m, int n)
{
/*
 * 1. 选主元：找到当前列中最大元素的行号
 * 2. 交换行，将主元（最大值）交换到对角线
 * 3. 计算其它行相对主元的消元系数，消元
 */
    int i, j, ex;
    double **A, **ahead, *ptmp;

    ahead = A = (double **)malloc(sizeof(double *) * m);
    for (i = 0; i < m; i++) {
        ptmp = (double *)malloc(sizeof(double) * (m+1));
        memcpy(ptmp, *M++, sizeof(double)*(m+1));
        *A = ptmp;
        A++;
    }
    A = ahead;

    // 按列扫描. 
    // 方阵最后一列无需消元，不予考虑
    // 同样因为当前增广矩阵最后一列为b值，无需消元，所以不予考虑
    for (i = 0; i < n-2; i++){

        float tmp_max = 0;
        int max_id = -1;

#ifdef DEBUG
    printf("初始矩阵为：\n");
    output_A(A, n, n);
    printf("\n");
#endif
        // 选主元：找到当前列中最大元素的行号
        for (j = i; j < m; j++){
            float e;
            e = fabs(A[j][i]);
#ifdef DEBUG
    printf("find max element ...\ni = %d, j = %d\n", i, j);
    printf("e = %f, A[%d][%d]= %f\n\n", e, j, i, A[j][i]);
#endif
            if ( e > tmp_max ){
                tmp_max = e;
                max_id = j;
            }
#ifdef DEBUG
    printf("e = %f, tmp_max = %f, A[%d][%d]= %f\n\n", e, tmp_max, j, i, A[j][i]);
#endif
        }
#ifdef DEBUG
    printf("max_id = %d\n", max_id);
    output_A(A, m, n);
    printf("\n");
#endif
        float tmp = 0.0;
        // 交换行
        for (ex = i; ex < n; ex++){
            tmp = A[i][ex];
            A[i][ex] = A[max_id][ex];
            A[max_id][ex] = tmp;
        }

#ifdef DEBUG
    printf("exchange ...\n");
    output_A(A, m, n);
    printf("\n");
#endif

#ifdef DEBUG
    printf("\nStart eliminating...\n");
#endif
        // 消元
        for (j = i + 1; j < m; j++){
            double co = 0.0;
            co = A[j][i] / A[i][i];
#ifdef DEBUG
    printf("The coff is %f\n", co);
#endif
            int cur;
            for (cur = i; cur < n; cur++){
                A[j][cur] -= A[i][cur] * co;
            }
        }
        if ( fabs(A[i][i]) < 1.0E-7 ){
            printf("the determinate is zero\n");
            return NULL;
        }
#ifdef DEBUG
    printf("i = %d ...\n", i);
    output_A(A, m, n);
    printf("\n\n");
#endif
    }

    return ahead;
}

void output_A(double **A, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
        #ifdef DEBUG_OUTPUT
            printf("A[%d][%d]=%.4lf\t",i,j, A[i][j]);
        #else
            printf("%9.4lf", A[i][j]);
        #endif
        }
        printf("\n");
    }
}

double **readMatrix(const char *file_name, int *m, int flags)
{
// 从文件中读取矩阵数据，第一个数据为整型，说明方阵的维度
    FILE *f;
    int i, j, n;
    double **p, **pHead, *tmp;

#ifdef DEBUG
    printf("reading ... %s\n", file_name);
#endif
    f = fopen(file_name, "r");
    fscanf(f, "%d", m);
    // 懒得改参数, so...
    n = *m;
    printf("矩阵为 %d 阶\n", n);

    pHead = p = (double **)malloc(n * sizeof(double *));

    for (i = 0; i < n; i++) {
        tmp = *p + i;
        tmp = calloc(sizeof(double), n+1);
        for (j = 0; j < n+flags; j++) {
            fscanf(f, "%lf", &tmp[j]);
#ifdef DEBUG_FILE
    printf("%f ", tmp[j]);
#endif
        }
#ifdef DEBUG_FILE
        printf("\n");
#endif
        *p++ = tmp;
    }
    return pHead;
}

double **solve(double **M, int n)
{
// 将result定义为二级指针主要是为了方便使用统一的输出函数
// 别无他意
    double **result, tmp = 0;
    int i, j;
    result = (double **)malloc(sizeof(double *));
    *result = calloc(sizeof(double), n);

    for (i = n - 1; i >= 0; i--) {
        result[0][i] = 0;
        tmp = 0.0;
        for (j = 1; j <= n-1-i; j++) {
            tmp += M[i][i+j] * result[0][i+j];
        }
        result[0][i] = (M[i][n] - tmp) / M[i][i];
#ifdef PRINT_RESULT
    printf("result[%d] = %lf\t", i, result[0][i]);
#endif
    }
    return result;
}

double **invers(double **M, double **MI, int n)
{
    int i, j;
    double **matrix_Inverse, **phead, **pmhead = M;
    double **tmp;

    phead = matrix_Inverse = (double **)malloc(sizeof(double *) * n);

    M = pmhead;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            M[j][n] = MI[j][i];
#ifdef DEBUG_INVERSE
        printf("当前矩阵为:\n");
        output_A(M, n, n+1);
#endif
        tmp = eliminate((const double **)M, n, n+1);
        tmp = solve(tmp,n);
        *matrix_Inverse++ = *tmp;
    }
    return phead;
}

double **matrix_I(int n)
{
    double **M_I, **phead, *tmp;
    int i;

    phead = M_I = (double **)malloc(sizeof(double *) * n);

    // 因为用calloc分配空间时，会自动清零，所以只用单循环就可以
    for (i = 0; i < n; i++) {
        tmp = calloc(sizeof(double), n);
        tmp[i] = 1;
        *M_I++ = tmp;
    }
    return phead;
}

void revers(double **M, int row, int col)
{
    int i, j;
    double tmp;

    for (i = 0; i < row; i++) {
        for (j = i+1; j < col; j++) {
            tmp = M[i][j];
            M[i][j] = M[j][i];
            M[j][i] = tmp;
        }
    }
}

double** multi(double **A, double** B, int n)
{
    double **C, **chead, *tmp;
    int i, j, k;

    chead = C = (double **)malloc(sizeof(double *)*n);
    for (i = 0; i < n; i++) {
        tmp = calloc(sizeof(double), n);
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++)
                tmp[j] += A[i][k] * B[k][j];
        }
        *C++ = tmp;
    }
    return chead;
}
