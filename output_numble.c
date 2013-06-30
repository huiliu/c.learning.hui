#include <stdio.h>

int main ( void )
{
    printf ( "Please Enter a numble:" );

    unsigned int ui_x;

    scanf ( "%d", &ui_x );

    unsigned ui_i = ui_x;

    for ( ; ui_i <= ui_x + 5; ui_i++ )
	printf ( "%d\t", ui_i );
  //循环运行了6次，输出5，6，7，8，9，10
   //应该是先进行条件判断(ui_i<=ui_x+5),符合条件则执行下面的程序段，然后再执行变量加减(ui_i++)，接着再判断条件…… 

    printf ( "the end cyclevar is:%d\n", ui_i );

    ui_i = ui_x;

    while ( ui_i <= ui_x + 5 )
    {
	ui_i++;	//注意此句位置不同，输出結果不同
	printf ( "%d \n", ui_i);

    }
    printf ( "the end cyclevar is:%d\n", ui_i );
    
    
    return 0;

}
