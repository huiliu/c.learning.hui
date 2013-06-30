/*
 * 第六章关于指针部分的一些练习：
 *
 *  主要包括：
 *      不用系统宏，用指针实现字符串的连接，比较等
 *
 */

#include <stdio.h>
#include <string.h>


#define DEBUG

void question01(void);
void flip_sign(int *p, int n);
int question02(char *str, char c);
char question04(char *str, char *substr);
char *question05_strncat(char *s1, char *s2, int n);
int question06_strncmp(char *s1, char *s2, int n);
char *question07_strncpy(char *s1, char *s2, int n);

int question08_main(void);
int question08_readData(char *fname, int *p);
float question08_average(int *p);
void question08_diff(int *p, int *result, int average);


int main(int argc, char ** argv)
{
    int n;
    char p[10] = "abc";
    char c[] = "def";

    question01();
    n = question02("liuhui", 's');
    printf("n = %d\n", n);
    printf("c = %c\n", question04("talk about the black bird", "blue"));

    question05_strncat(p, c, 3);

    n = question06_strncmp(p, c, 6);
    printf("n = %d\n", n);

    question07_strncpy(p, c, 4);

    question08_main();
    return 0; 
}

void question01(void)
{
    int A[] = {1,2,3,4,5};
    int i;
    flip_sign(A, 5);
    for (i = 0; i < 5; i++)
        printf("%d\t", *(A + i));
}
void flip_sign(int *p, int n)
{
    // 利用指针，将一个数组元素反号
    int i;
    for (i = 0; i < n; i++){
        *p = -*p++;
        #ifdef DEBUG
        printf("%d\t", *(p -1));
        #endif
    }
}

int question02(char *str, char c)
{
    // 利用指针，判断一个字符是否在字符串中
    if (strchr(str, c) != NULL)
        return 1;
    else
        return 0;
}

char question04(char *str, char *substr)
{
    char *p;
    if ((p = strstr(str, substr)) != NULL)
        return *p;
    else
        return NULL;
}

// 利用指针实现字符串连接
char *question05_strncat(char *s1, char *s2, int n)
{
    int i, len;

    if (s1 == NULL || s2 == NULL)
        return NULL;

    len = strlen(s1);

    //for (i = 0; i < n; i++){
    //    *(s1 + len + i) = *(s2 + i);
    //}

    char *p = s1 + len;
    for (i = 0; i < n; i++){
        *p++ = *s2++;
    }
    #ifdef DEBUG
    printf("%s\n", s1);
    #endif

    return s1;
}

// 用指针实现strncmp
int question06_strncmp(char *s1, char *s2, int n)
{
    int i, len;
    int m;

    if (s1 == NULL || s2 == NULL)
        return NULL;

    len = strlen(s1);
    n = n > len ? len: n;
    for (i = 0; i < n; i++){
        m = (int)*s1++ - (int)*s2++;
        if ( m == 0)
            continue;
        else
            return m;
    }
    return 0;
}

// 用指针实现strncpy
char *question07_strncpy(char *s1, char *s2, int n)
{
    int i;

    if (strlen(s2) < n){
        printf("the length of string 2 < %d\n", n);
        return NULL;
    }

    for (i = 0; i < n; i++){
        *s1++ = *s2++;
    }
    #ifdef DEBUG
    printf("%s\n", s1);
    #endif
    return s1;
}

// 从文件中读入100个整型数据，计算其平均值，并计算每个数与平均值之差
#define NUMBER_COUNT    100
int question08_main(void)
{
    int data[NUMBER_COUNT], mn[NUMBER_COUNT];
    float average;
    char *fn = "test/data";

    if (question08_readData(fn, data) != 0)
        return 1;
    average = question08_average(data);
    question08_diff(data, mn, average);
    return 0;
}

int question08_readData(char *fname, int *p)
{
    FILE *fp;
    int i;

    if ((fp = fopen(fname, "r")) == NULL){
        printf("打开文件失败!");
        return 1;
    }
    for (i = 0; i < NUMBER_COUNT; i++){
        fscanf(fp, "%d", p + i);
    }
    fclose(fp);
    return 0;
}

float question08_average(int *p)
{
    int sum = 0;
    int i;
    float average;
    for (i = 0; i < NUMBER_COUNT; i++)
        sum += *p++;
    average = (float)sum /NUMBER_COUNT;
    #ifdef DEBUG
    printf("Sum = %d\tAverage = %f\n", sum, average);
    #endif
    return average;
}

void question08_diff(int *p, int *result, int average)
{
    int i, m;
    
    for (i = 0; i < NUMBER_COUNT; i++){
        m = *p++;
        *result++ = m - average;
        #ifdef DEBUG
        printf("%d\t", *(result - 1));
        #endif
    }
}
