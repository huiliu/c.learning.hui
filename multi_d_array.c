/*
 *
 * 从文件中读取数据存入数组，进行一个简单的矩阵乘法
 *
 * 默认数据文件为：./matrix.data
 */


#include <stdio.h>

// 设定矩阵的行，列数
#define N   2

int ReadMatrix(int [][N], int [][N]);
void outputMatrix(int [][N]);
int MatrixProduct();

int main(int argc, char **argv)
{
    MatrixProduct();
    return 0;
}

// 从文件中读取矩阵数据
int ReadMatrix(int A[][N], int B[][N])
{
    int i, j;
    FILE *f;
    char fname[] = "matrix.dat";

    if ((f = fopen(fname, "r")) == NULL){
        printf("Open the file '%s' failed\n", fname);
        return 1;
    }
    
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if(fscanf(f, "%d", &A[i][j]) == EOF && i * j != (N-1) * (N-1)){
                printf("Read Error!");
                fclose(f);
                return 2;
            }
            B[i][j] = A[i][j];
            //printf("%d\t", A[i][j]);
        }
        //printf("\n");
    }
    fclose(f);
    outputMatrix(A);
    return 0;
}

// 进行矩阵乘法计算
int MatrixProduct()
{
    int A[N][N], B[N][N], C[N][N];
    int i, j, k;

    if(ReadMatrix(A, B))
        return 1;

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            // 注意一定初始化，否则一定出错
            C[i][j] = 0;
            for (k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
            //printf("C[%d][%d] = %d\t", i, j, C[i][j]);
        }
        //printf("\n");
    }
    outputMatrix(C);
    return 0;
}

// 输出矩阵
void outputMatrix(int A[][N])
{
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            printf("A[%d][%d] = %d\t", i, j, A[i][j]);
        printf("\n");
    }
}
