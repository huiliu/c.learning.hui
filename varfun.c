#include <stdio.h>
#include <stdarg.h>

double average(int count, ...)
{
    int i, sum = 0;
    va_list vlist;

    va_start(vlist, count);

    for (i = 0; i < count; i++) {
        sum += va_arg(vlist, int);
    }
    va_end(vlist);

    fprintf(stdout, "Average: %lf\n", (double)sum / count);
    return 0; 
}

int main(int argc, char** argv)
{
    average(3, 4, 5, 6);
    return 0;
}
