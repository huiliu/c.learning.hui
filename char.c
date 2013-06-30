#include <stdio.h> 
#include <string.h> 

int main(int argc, char **argv)
{
    char text[20] = "Hello World!";
    int i;
    
    strcpy(text, argv[1]);
    for (i = 0; i < 20; i++)
        printf("%c", text[i]);
    printf("\n");

    printf("%s\n", text);
    return 0;
}
