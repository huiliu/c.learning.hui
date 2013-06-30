#include <stdio.c>


int main(int argc, char **argv)
{
    printf("you type in %d parameter from command\n", argc);
    int i = 0;
    for (i = 0; i < argc; i++)
        printf("%s\n", argv[i]);

    return 0;
}
