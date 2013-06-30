/*****************************************
  *
  *C允许输出八进制、十进制、十六进制三种数据形式
  *
*****************************************/


#include <stdio.h>
#include <inttypes.h>

int main ( void )
{
    int x = 100;
    int16_t me16 = 4593;

    printf ( "Dec = %d; Octal = %o; Hex = %x\n", x, x, x);
    printf ( "Dec = %d; Octal = %#o; Hex = %#x\007", x, x, x);

}

