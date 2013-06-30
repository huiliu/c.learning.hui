/*
 * 此部分代码主要用于格式化文件，將一个文本文件格式化
 *　为每行LINE_LEN个字符，如果不足，则用插入空格补充，
 *　且空格插入要求比较均匀。
 *
 * TODO:
 *  智能化插入空格
 *
 */

#include <stdio.h>
#include <string.h>


// 读入的最多字符串数
#define TEXT_LEN    300
// 每行字符数
#define LINE_LEN    80
// 每个字符的最长长度
#define WORD_MAX    20

int output(int start, int cur, int l, char p[][WORD_MAX]);

int main(int argc, char **argv)
{
    FILE *fp;
    char text[TEXT_LEN][WORD_MAX], tmp[WORD_MAX];
    //int len[TEXT_LEN];
    int i, start, line = 0;
    char LF = (char)10;

    if (argc == 1){
        printf("请输入需要格式化的文件名。\n");
        return 1;
    }else if ((fp = fopen(argv[1], "r")) == NULL){
        printf("打开文件错误！\n");
        return 1;
    }

    for (i = 0; i < TEXT_LEN; i++){
        if (fscanf(fp, "%s", tmp) == EOF)
            break;
        if (strncmp(tmp, &LF, 1) == 0)
            continue;
        strcpy(text[i], tmp);
        if (line == 0)
            start = i;

        line += (strlen(text[i]) + 1);

        int state = output(start, i, line, text);
        if (state == 1){
            #ifdef DEBUG
            printf("n = %d\n", line);
            #endif
            start = i + 1;
            line = 0;
        }else if (state == 2){
            #ifdef DEBUG
            printf("n = %d\n", line);
            #endif
            start = i;
            line = (strlen(text[i]) + 1);
        }else
            continue;
    }
    #ifdef DEBUG
    for (i = 0; i < TEXT_LEN; i++)
        printf("%s ", text[i]);
    #endif
    return 0;
}

// 进行判断输出
int output(int start, int cur, int l, char p[][WORD_MAX])
{
    int j;

    // +1是因为第个字符后都会增加一个空格，
    // 而如果当前行到最后一个单词，刚好LINE_LEN个字符，则
    // 不需要加一个空格
    //
    // 此做法可能不符合文法
    if (l == LINE_LEN + 1){
    // 行长刚好为LINE_LEN
        for (j =start; j < cur; j++){
            printf("%s ", p[j]);
        }
        printf("%s\n", p[j]);
        return 1;
    }else if ( l > LINE_LEN + 1){
    // 行长超过为LINE_LEN
        for (j = start; j < cur; j++){
            printf("%s ", p[j]);
        }
        printf("\n");
        return 2;
    }else
    // 行长小于为LINE_LEN
        return 0;
}
