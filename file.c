#include <stdio.h>
#include <string.h>

int example_fgets(char *fname);

int main(int argc, char **argv)
{
    example_fgets(argv[1]);    
    return 0;
}

int example_fgets(char *fname)
{
    FILE *fp;
    char str[10], *p;
    char NUL = '\0';
    char tmp = 'a';

    p = str;

    fp = fopen(fname, "r");

    strncpy(p+10, &tmp, 1);
    printf("%c\n", *(p + 10));
    p = fgets(str, 11, fp);
    if (strncmp(p+10, &NUL, 1) == 0)
        printf("越界成功!\n");
    else
        printf("%c\n", *(p + 10));
    printf("%sH\n", p);

    //p = fgets(str, 10, fp);
    //printf("%s H\n", p);

    fclose(fp);

    return 0;
}
