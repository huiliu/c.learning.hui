#include <stdio.h>


int main ( void )
{
    int int_x = 5;

    printf ( "%d\n", int_x );
    printf ( "%d\n", int_x *= 2 );
    printf ( "%d\n", int_x );
    return 0;
}



/*******************************************************************
  *
  *一元运算符：＋＋、－－在操作数左侧时先运算后赋值，在右侧时先赋值后运算，即当前赋值仍赋原值（上次值）；＋＝、-=等运算后再赋值。
  *
  *
  *
  *
  *
  *
  */
