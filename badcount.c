/*
   *
   *
   *说明Printf的参数问题，格式说明符必须保证同后面的参数相同
   *
   *
   */

#include <stdio.h>

int main ( void )
{
    int f = 4;
    int g = 5;
    float h = 5.0f;

    printf ( "%d\n", f, g);	//参数太多
    printf ( "%d, %d\n", f);	//参数太少
    printf ( "%d, %f\n", h, g );	//值类型不正确
    return 0;
}
