//
// 特别注意scanf不能插入提示字符
// 包含一个简单的对有序数列进行二分查找的算法
// 二分算法还存在BUG，有些数据可能被跳过，一直打不到
//
//  测试文件为: test/student
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN 255
#define RECORD_LEN  113
#define ITEM_LEN    7
#define PRINT_NUM   10

//#define DEBUG

int ReadData(const char fname[], char item[][ITEM_LEN][STR_LEN]);
int outputData(int, char data[][ITEM_LEN][STR_LEN]);
int sort(char data[][ITEM_LEN][STR_LEN]);
void search(char data[][ITEM_LEN][STR_LEN], char pattern[STR_LEN], char result[ITEM_LEN][STR_LEN]);
int b_search(char data[][ITEM_LEN][STR_LEN], char pattern[STR_LEN], char result[ITEM_LEN][STR_LEN]);

int main(int argc, char **argv)
{
    char item[RECORD_LEN][ITEM_LEN][STR_LEN];

    if (argc < 2){
        printf("Please enter the file name!\n");
        return 1;
    }
    #ifdef DEBUG
    printf("%d\n", argc);
    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    #endif
    ReadData(argv[1], item);

    printf("排序前：\n");
    outputData(PRINT_NUM, item);
    printf("排序后：\n");
    sort(item);
    outputData(PRINT_NUM, item);


    char str_s[STR_LEN], result[ITEM_LEN][STR_LEN];
    printf("\n测试查找功能：\n");
    printf("请输入您要查找的字符:"); 
    scanf("%s", str_s);
    search(item, str_s, result);
    #ifdef DEBUG
    printf("你输入的为：%s\n", str_s);
    #endif
    printf("\n测试二分查找功能：\n");
    printf("请输入您要查找的字符:"); 
    scanf("%s", str_s);
    b_search(item, str_s, result);
    return 0;
}

int ReadData(const char fname[], char item[][ITEM_LEN][STR_LEN])
{
    FILE *fp;
    //char item[RECORD_LEN][ITEM_LEN][STR_LEN];
    int i, j;

    if ((fp = fopen(fname, "r")) == NULL){
        printf("Read File Failed!");
        fclose(fp);
        return 1;
    }

    for (i = 0; i < RECORD_LEN; i++){
        for (j = 0; j < ITEM_LEN; j++){
            //fgets(item, STR_LEN, fp);
            fscanf(fp, "%s", item[i][j]);
            //printf("%s\t", item[i][j]);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}

int outputData(int num, char data[][ITEM_LEN][STR_LEN])
{
    int i, j;
    for (i = 0; i < num; i++){
        for (j = 0; j < ITEM_LEN; j++)
            printf("%s\t", data[i][j]);
        printf("\n");
    }
    return 0;
}

int sort(char data[][ITEM_LEN][STR_LEN])
{
    // 特别注意对字符串的操作必须使用字符串函数
    // 比较strcmp, 赋值strcpy
    int i, j, k;
    char tmp[STR_LEN];

    for (i = 0; i < RECORD_LEN; i++){
        for (j = 0; j < RECORD_LEN; j++){
            if (strcmp(data[i][0], data[j][0]) < 0){
                for (k = 0; k < ITEM_LEN; k++){
                    strcpy(tmp, data[i][k]);
                    strcpy(data[i][k], data[j][k]);
                    strcpy(data[j][k], tmp);
                }
            }
        }
    }
    return 0;
}

void search(char data[][ITEM_LEN][STR_LEN], char pattern[STR_LEN], 
                char result[ITEM_LEN][STR_LEN])
{
    int i, j, k;
    printf("正在查找关键字'%s'... ...\n", pattern);
    for (i = 0; i < RECORD_LEN; i++){
        for (j = 0; j < ITEM_LEN; j++){
            if (strcmp(data[i][j], pattern) == 0){
                for (k = 0; k < ITEM_LEN; k++){
                    strcpy(result[k], data[i][k]);
                    printf("%s\t", data[i][k]);
                }
                printf("\n");
            }
        } 
    }
}

int b_search(char data[][ITEM_LEN][STR_LEN], char pattern[STR_LEN], 
                char result[ITEM_LEN][STR_LEN])
{
    // 用于查找有序数据
    // 二分查找
    // 存在BUG需要修订
    // 有一些数据可能会查找不到
    printf("正在查找关键字'%s'... ...\n", pattern);

    int pre, cur, half;
    int i, n;
    pre = 0; cur = 0; half = (RECORD_LEN - 1) / 2;

    while (1){
        #ifdef DEBUG
        printf("pre = %d\thalf = %d\tValue = %s\n", pre, half, data[half][0]);
        #endif
        n = strcmp(pattern, data[half][0]);
        if (n == 0){
            for (i = 0; i < ITEM_LEN; i++)
                printf("%s\t", data[half][i]);
            printf("\n");
            return 0;
        }else if (n < 0){
            cur = half;
            if (! (half - pre) % 2 == 0)
                half = half - abs(half - pre - 1) / 2;
            else
                half = half - abs(half - pre) / 2;
            pre = cur;
        }else if (n > 0){
            cur = half;
            if (! (half - pre) % 2 == 0)
                half = half + abs(half - pre - 1) / 2;
            else
                half = half + abs(half - pre) / 2;
            pre = cur;
        }
        i++;
        // 防止查找不到的数据进入死循环
        // 112, 56, 28, 14, 7, 3, 2, 1, 0
        // 所有数据应该在10步以内可以查到
        if (i > 15)
            return 1;
    }
}
