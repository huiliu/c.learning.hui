#include <stdio.h>
#include <string.h>

//
// 此程序主要用于测试学习各个字符串操作函数
//
#define DEBUG

void combinate();
void compare();
void output(int, char [], char []);
void str_copy();
void str_len();
void str_search();

int main(int argc, char **argv)
{
    combinate();
    compare();
    str_copy();
    str_len();
    str_search();
    return 0;
}

void combinate()
{
    char string1[6] = "hello";
    char string2[6] = "world";

    printf("测试比较strcat与strncat的差别:\n");
    #ifdef DEBUG
    printf("string1 = '%s'\n", string1);
    printf("string2 = '%s'\n", string2);
    #endif
    // 此处也说明字符后不会自动加上空格
    // 注意strcat和strncat都会返回操作后形成的一个新字符串
    // 内容与string1相同
    // 不知道是不是返回的是不是地址
    #ifdef DEBUG
    printf("strcat(str1, str2) return: %s\n",strcat(string1, string2));
    printf("-------after strcat-------\nstr1 = %s\n", string1);
    #else
    printf("strcat(str1, str2) return: %s\n",strcat(string1, string2));
    printf("-------after strcat-------\nstr1 = %s\n", string1);
    #endif
    printf("str2 = %s \nstrcat doesn't change string2\n", string2);

    char string3[6] = "hello";
    char string4[6] = "world";
    printf("strncat(s1, s2, n) return: %s\n", strncat(string3, string4, 2));
    printf("-------after strncat-------\nstr3 = %s\n", string3);
    printf("str4 = %s \nstrncat doesn't change string4\n", string4);
}

// 字符串比较函数
void compare()
{
    printf("\n字符串比较函数测试strcmp, strncmp:\n");
    
    int i, j, k;
    char a[] = "hello", b[] = "hello";
    i = strcmp(a, b);
    output(i, a, b);

    char c[] = "helIo", d[] = "hello";
    j = strcmp(c, d);
    output(j, c, d);

    char e[] = "hello", f[] = "helIo";
    k = strcmp(e, f);
    output(k, e, f);

    char string1[] = "gladiator";
    char string2[] = "gladiolus";
    // 比较从左端开始的几个字符
    printf("--------strncmp----------\n");
    printf("strncmp = %d\n", strncmp(string1, string2, 5));
}

void output(int ii, char a[], char b[])
{
    if (ii == 0)
        printf("%s = %s\n", a, b);
    else if(ii < 0)
        printf("%s < %s\n", a, b);
    else
    //else if(ii > 0)
        printf("%s > %s\n", a, b);
}

void str_copy()
{
    // 测试发现：
    // 函数strpy(string1, string2)会将string1内容替换为string2
    // 如果string 定义为char string1[100]; strcpy只会覆盖string2长度
    // 的字符串，而不会将超过此范围的字符串清空
    // 但是只打印字符串时，不会打印其它部分, 如果循环打印字符就会发现其它字符
    // 其实还在
    // 函数strnpy(string1, string2, n)会将string1左侧的n个字符替换
    // 为string2左侧的n个字符
    //
    // strcpy与strncpy返回第一个字符串的地址，即copy后的操作结果

    printf("\n比较strcpy与strncpy的差别:\n");
    printf("--------strcpy---------\n");
    char a[] = "hello";
    char b[] = "hi";

    printf("a = '%s'\tb = '%s'\n", a, b);
    printf("a + b = %s\n", strcpy(a, b));
    printf("a + b = %s\n", a);

    printf("--------非等长strcpy---------\n");
    char c[6] = "hello";
    char d[3] = "hi";
    printf("c + d = %s\n", strcpy(c, d));
    printf("c = %s\n", c);

    printf("----循环打印----\nc = ");
    int i;
    char aaa = '\0';
    for (i = 0; i < 6; i++){
        // 证明每个字符串结尾有一个\0标识
        if (strncmp(c + i, &aaa, 1) == 0)
            printf(" ");
        else
            printf("%c", c[i]);
    }
    printf("\n");

    char e[] = "hello";
    char f[] = "hi";
    printf("--------strncpy---------\n");
    printf("a = '%s'\tb = '%s'\n", e, f);
    printf("a + b = %s\n", strncpy(e, f, 2));
    printf("a = %s\n", e);
}

void str_len()
{
    // 函数strlen用于取得字符串的长度:
    printf("-----------strlen-----------\n");
    char str1[] = "hello";
    printf("the length of '%s' is: %d\n", str1, (int)strlen(str1));
    printf("the length of '%s' is: %d\n", "  ", (int)strlen("  "));
}

void str_search()
{
    //strstr, strchr, strrchr
    /*
     * strstr(str1, str2)   在str1中查找子字符
     * strchr(str1, chr)    在str1中正向查找字符chr 
     * strrchr(str1, chr)    在str1中逆向查找字符chr 
     *
     * 这个三个函数都会返回从字串匹配位置开始到结尾部分
    */
    printf("\n测试字符串查找:\n");
    char string1[] = "Hello World!";
    char str2[] = "World";
    char char1 = 'l';

    printf("%s in %s : %s\n", str2, string1, strstr(string1, str2));
    printf("%c in %s : %s\n", char1, string1, strchr(string1, char1));
    printf("%c in %s : %s\n", char1, string1, strrchr(string1, char1));
}
