#include <stdio.h>

/*
 *This programe is demonstrated bell and so on
 */

int main ( void )
{
	printf("Hello world!\r");
	// Herizontal tab
	printf("水平制表符\t");
	printf("after herizontal tab\n");

	printf("\a");
	//vertical tab
	printf("垂直制表符\v");
	printf("vertical tab\n");
/*
 *The text output:(where is the "Hello World!"?)
 *
 *水平制表符d!    after herizontal tab
 *垂直制表符
 *          vertical tab
 */
	return 0;
}

