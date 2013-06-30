#include <stdio.h>

void cmp(void);
void output_big(void);
int ordered(void);

int main(int argc, char **argv)
{
    int income, tax;
    FILE    *fin,   *fout;
 
    //　改进版，可以由用户输入文件名
    char fname;
    printf("Please type in the input file name: ");
    scanf("%s", &fname);
    printf("%s\n", &fname);
    fin = fopen(&fname, "r");

    if (fin == NULL) {
        printf("open file failed!\n");
        return 1;
    }

    //fin = fopen("in.dat", "r");
    fout = fopen("out.dat", "w");

    while(fscanf(fin, "%d", &income) != EOF){
        fprintf(fout, "Income = %d\n", income);
        if(income <= 0){
            tax = 0;
            fprintf(fout, "这个公司处于亏损状态\n");
        }else if(income < 6000)
            tax = income * 0.3;
        else
            tax = income * 0.6;
        fprintf(fout, "Tax = %d \n", tax);
    }

    fclose(fin);
    fclose(fout);

    printf("\nTest read data from file and compare ...\n");
    cmp();
    printf("\nTest read data output the max and big data...\n");
    output_big();
    printf("\nDoes the number serials is ordered?  ");
    ordered();
    return 0;
}

// 从文件中读取整数，并输出最大与最小的
void cmp()
{
    int max, min, num;
    FILE *fin;

    max = 0; min = 0; num = 0;
    fin = fopen("in.dat", "r");
    while(fscanf(fin, "%d", &num) != EOF){
        if ( num > max )
            max = num;
        else if ( num < min )
            min = num;
    }

    fclose(fin);
    printf("Max = %d\nMin=%d\n", max, min);
}

// 从文件中读取整数，并输出最大与次大的
void output_big()
{
    int max, max2, num;
    FILE *fin;

    max = 0; max2 = 0; num = 0;
    fin = fopen("in.dat", "r");
    while(fscanf(fin, "%d", &num) != EOF){
        if ( num > max )
            max = num;
        else if ( num < max && num > max2 )
            max2 = num;
    }

    fclose(fin);
    printf("Max = %d\nMin=%d\n", max, max2);
}

// 判断数列是否有序
int ordered()
{
    int min, num;
    FILE *fin;
    
    min = -65323;
    fin = fopen("in.dat", "r");

    while ( fscanf( fin, "%d", &num) != EOF ){
        if ( num > min )
            min = num;
        else{
            //printf("the number serial isn't ordered.\n");
            printf("NO.\n");
            return 1;
        }
    }
    fclose(fin);
    printf("Yes\n");
    return 0;
}
