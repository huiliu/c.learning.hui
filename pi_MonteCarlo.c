#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("请输入一个整数!\n");
        exit(EXIT_FAILURE);
    }
    int i, n, s = 0;
    int a, b, c;
    double pi;

    printf("%s", argv[1]);
    n = atoi(argv[1]);
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        a = rand() / 3 % 100;
        b = rand() / 7 % 100;
        c = (a - 50)*(a - 50) + (b - 50)*(b - 50);
        if (c <= 2500)
            s++;
    }
    
    pi = 4 * (double)s / n;
    printf("Pi = %.10f\n", pi);
    return 0;
}
