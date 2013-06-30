/*******************************************
  *
  *
  *输出各种数据类型的大小
  *
  *
*******************************************/


#include <stdio.h>


int main ( void )
{
    printf ( "Type char has a size of %o bytes.\n", sizeof ( char ) );
    printf ( "Type int has a size of %o bytes.\n", sizeof ( int ) );
    printf ( "Type unsigned has a size of %o bytes.\n", sizeof ( unsigned ) );
    printf ( "Type short has a size of %o bytes.\n", sizeof ( short ) );
    printf ( "Type float has a size of %o bytes.\n", sizeof ( float ) );
    printf ( "Type double has a size of %u bytes.\n", sizeof ( double ) );
    printf ( "Type long has a size of %o bytes.\n", sizeof ( long ) );
    printf ( "Type long long has a size of %o bytes.\n", sizeof ( long long ) );

    return 1;
}
