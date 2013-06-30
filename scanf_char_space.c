#include <stdio.h>

void echo_char(void);
void echo_char_space(void);


void main(void)
{
    int i;
    printf("1. 无空格\n2. 有空格\n");
    scanf("%d", &i);
    if ( i == 1)
        echo_char();
    else if ( i == 2 ) 
        echo_char_space();
    else
        printf("输入错误!");
}

void echo_char(void)
{
    char s;
    s = 's';

    // 注意scanf "%c"格式字符串，如果% 与 "间有一个空格
    // 输入时情况大不一样
    while ( scanf("%c", &s) != '\0' ){
        printf("%c", s);
    }
}

// 测试scanf "%c"的空格效果
void echo_char_space(void)
{
    char s;
    s = 's';

    // 注意scanf "%c"格式字符串，如果% 与 "间有一个空格
    // 输入时情况大不一样
    while ( scanf(" %c", &s) != '\0' ){
        printf("%c", s);
    }
}
