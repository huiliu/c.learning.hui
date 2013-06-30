/************************************
  *
  *说明一些printf()的属性
  *
*************************************/

#include <stdio.h>

int main ( void ){
    int ten = 10;
    int two = 2;

    printf ("Doing it right: ");
    printf ("%d minus %d is %d\n", ten, 2, ten - two );

    printf ("Doing it right: ");
    printf ("%d minus %d is %d\n", ten);	//注意此处printf（）少了两个参数，注意它的输出值，the output may different in others system. It related to the value of the memory and different debug deal with the position in the memory is different. And many debug cann't find this bug, so you must be careful.


}
