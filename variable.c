#include <stdio.h>

void
var (void)
{
  int i;
  i = 10;

  int j;
  j = 20;

  printf ("%d\n%d\n", i, j);
}

int
main (void)
{
  var ();
  return 1;
}
