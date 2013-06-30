#include <stdio.h>

/*
 *此部分程序用于说明C中的各种赋值操作
 *
*/

int main ( void )
{
	int x, y;
	x = y = 0;
	printf("x = %d", x, " y = %d", y);

	printf("x += 1, x=%d",x += 1);	
	y -= 3;


}
