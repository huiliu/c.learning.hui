/*********************************************************************
  *
  *这段程序用于转换时间
  *
  */

#include <stdio.h>

#define SIX 60;

int
main (void)
{
  unsigned int i_minute = 1, i_m = 0, i_h = 0;


  while (i_minute > 0)
    {
      printf ("Please enter minutes:");
      scanf ("%d", &i_minute);
      //printf ("%d", i_minute);
      i_m = i_minute % SIX;
      i_h = i_minute / SIX;
      printf ("you enter time is %d hour %d minute\n", i_h, i_m);
    }


  return 0;

}
