#include <stdio.h>

int factorial(int);
int fibonacci(int);


int main(void)
{
   int x;
   printf("Please type in an integer number: ");
   scanf("%d", &x);

   printf("factorial(%d) = %d\n", x, factorial(x));
   printf("fibonacci(%d) = %d\n", x, fibonacci(x));
   return 0;
}

// recursive function demo
int factorial(int n)
{
    if ( n <= 1 )
        return 1;
    else
        return n * factorial(n-1);
}

int fibonacci(int n)
{
//    printf("%d\t", n);
    if ( n <= 2 )
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}
