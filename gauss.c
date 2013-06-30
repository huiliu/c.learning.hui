#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 
int eliminate(double A[][3], int m, int n);
void output_A(double A[][3]);
void readMatrix(const char *, float data[][3]);

int main(void)
{
    double A[3][3] = {{6,2,2},{2,2.0/3,1.0/3},{1,2,-1}};

    int state = eliminate(A, 3, 3);
    if (state)
        exit(EXIT_FAILURE);

    printf("print result ...\n");
    output_A(A);
/*
    char fname;
    float B[3][3];
    printf("Read Matrix data from file : ");
    scanf("%s", &fname);
    readMatrix(&fname, B);

    output_A(B);
*/
    return 0;

}

int eliminate(double A[][3], int m, int n)
{
    //float A[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int i, j, ex;

    // 按列扫描
    for (i = 0; i < 3; i++){

        float tmp_max = 0;
        int max_id = -1;

#ifdef DEBUG
    printf("初始矩阵为：\n");
    output_A(A);
    printf("\n");
#endif
        // 选主元：找到当前列中最大元素的行号
        for (j = i; j < 3; j++){
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
    output_A(A);
    printf("\n");
#endif
        // 交换行
        for (ex = i; ex < 3; ex++){
            float tmp = 0.0;
            tmp = A[i][ex];
            A[i][ex] = A[max_id][ex];
            A[max_id][ex] = tmp;
        }

        #ifdef DEBUG
        printf("exchange ...\n");
        output_A(A);
        printf("\n");
        #endif

        #ifdef DEBUG
        printf("\nStart eliminating...\n");
        #endif
        // 消元
        for (j = i + 1; j < 3; j++){
            float co = 0.0;
            co = A[j][i] / A[i][i];
            #ifdef DEBUG
            printf("The coff is %f\n", co);
            #endif
            int cur;
            for (cur = i; cur < 3; cur++){
                A[j][cur] -= A[i][cur] * co;
            }
        }
        if ( A[i][i] == 0.0 ){
            printf("the determinate is zero\n");
            //return 1;
        }
        #ifdef DEBUG
        printf("i = %d ...\n", i);
        output_A(A);
        printf("\n\n");
        #endif
    }

    return 0;
}

void output_A(double A[][3])
{
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("A[%d][%d]=%.4lf\t",i,j, A[i][j]);
        }
        printf("\n");
    }
}

void readMatrix(const char *file_name, float data[][3])
{
    FILE *f;
    int i, j;

    printf("reading ... %s\n", file_name);
    f = fopen(file_name, "r");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            fscanf(f, "%f", &data[i][j]);
            #ifdef DEBUG
            printf("%f\n", data[i][j]);
            #endif
        }
    }
}
