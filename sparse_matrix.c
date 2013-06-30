/*
 * 此程序主要演示了稀疏矩阵的存放和加法操作，关于乘法操作，由于没有看懂所以...
 *
 * 程序的关键部分fastTranspose取自
 * H. Ellis, S. Sartaj, A. F. Susan, Fundamentals of Data Structures in C (2ed)
 * 
 * Date: Tue Jun 19 19:42:59 CST 2012
 *
 */

#include <stdio.h>

#define DEBUG   0
#define MAX_COL 10
typedef struct {
    //  二维数组中的col指标
    int col;
    // 二维数组中的row指标
    int row;
    // 数组中对应的数值
    int value;
    }term;

void initTerm(term *a, int row, int col, int value);
term *fastTranspose(term *a, term *b);
void outputMatrx(term *d, int n);

int main(int argc, char **argv)
{
    term a[9], b[9];
    //第一元素的col, row为稀疏矩阵的列和行数，value为非零元素的数目
    initTerm(a, 6, 6, 8);

    initTerm(a+1, 0, 0, 15);
    initTerm(a+2, 0, 3, 22);
    initTerm(a+3, 0, 5, -15);
    initTerm(a+4, 1, 1, 11);
    initTerm(a+5, 1, 2, 3);
    initTerm(a+6, 2, 3, 6);
    initTerm(a+7, 4, 0, 91);
    initTerm(a+8, 5, 2, 28);
    /*
        15  0   0   22  0   -15  
        0   11  3   0   0   0
        0   0   0   6   0   0
        0   0   0   0   0   0
        91  0   0   0   0   0
        0   0   28  0   0   0
     */


    fastTranspose(a, b);

    outputMatrx(a, 9);
    outputMatrx(b, 9);

    return 0;
}

//转置
term *fastTranspose(term *a, term *b)
{
    // rowTerm[i] 存放着转置后第i行的非零元素个数
    // startingPos[i] 为第i行的起始位置
    int rowTerm[MAX_COL], startingPos[MAX_COL];
    // Array[0].row, Array[0].col, Array[0].value 分别存放着当前稀疏
    // 矩阵的行数，列数，非零元素数目.
    int i, j, numCols = a[0].col, numTerms = a[0].value;

    b[0].row = numCols, b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < numCols; i++)
            rowTerm[i] = 0;

        // 得到每一列非零元素的数目
        // 即rowTerm[0] 存放着原spare matrix中第0列的非零元素数目
        for (i = 1; i <= numTerms; i++)
            rowTerm[a[i].col]++;

        // 理解startingPos最为重要
        // startingPos 存放着每列元素在三元组数组中的起始位置
        startingPos[0] = 1;
        for (i = 1; i <= numCols; i++)
            startingPos[i] = startingPos[i-1] + rowTerm[i-1];

        // 遍历所有非零元素
        for (i = 1; i <= numTerms; i++) {
            // 获取当前非零元素所在列的初始位置，转置一个后移一位
            j = startingPos[a[i].col]++;

            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
#if DEBUG
    for (i = 0; i < numCols; i++)
        printf("i = %d\t rowTerms = %d\tstartPos = %d\n", \
                    i, rowTerm[i], startingPos[i]);
#endif
    return b;
}

void initTerm(term *a, int row, int col, int value)
{
    a->col = col;
    a->row = row;
    a->value = value;
}

void outputMatrx(term *d, int n)
{
    int i;
    static int j = 0;
    printf("第%d个矩阵为：\n", j++);
    for (i = 0; i < n; i++) {
        printf("i = %d\trow = %d\tcol = %d\tvalue = %d\n", \
                i, d[i].row, d[i].col, d[i].value);
    }
}
