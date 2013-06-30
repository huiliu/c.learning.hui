#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX_CHAR   80

int fmt(char *);
void test_char();

int main(int argc, char **argv)
{
    test_char();
    //fmt(argv[1]);
    return EXIT_SUCCESS;
}

int fmt(char *fname)
{
    FILE *f;
    // 从命令行参数得到文件名
    if ((f = fopen((const char *)fname, "r")) == NULL){
        printf("Failed to open the file \"%s\", Please check it exist.", fname);
        return 1;
    }
        
    char word[LINE_MAX_CHAR + 1];
    int word_len, cur_line_len;

    while (fscanf(f, "%s", word) != EOF){
        for (word_len = 0; word[word_len] != '\0'; word_len++)
            ;
        if (word_len > LINE_MAX_CHAR){
            printf("The word's length exceeds line length.\n");
            return 1;
        }else if (cur_line_len == 0){
            printf("%s ", word);
            cur_line_len = word_len;
        }else{
            cur_line_len += word_len;
            if (cur_line_len > LINE_MAX_CHAR){
                printf("\n%s ", word);
                cur_line_len = word_len;
            }else
                printf("%s ", word);
        }

    }
    fclose(f);
    return EXIT_SUCCESS; 
}

//这个函数用于测试字符后面\0问题
//scanf函数会以空格来分隔word, 但打印时此空格并不包含其中，需要手动添加
void test_char()
{
    char inchar[10];
    printf("Please enter some words: ");
    scanf("%s", inchar);
    // 打印时，printf不会在字符串后补加一个空格
    printf("%s", inchar);
    int i;
    for (i = 0; inchar[i] != '\0'; i++)
        printf("%c", inchar[i]);
}
