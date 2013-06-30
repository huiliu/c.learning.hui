#include <stdio.h>

#define EE1 "a"
#define E(b)    EE1##b
int main(int argc, char **argv)
{
    fprintf(stdout, "%s\n", E("c"));
    return 0;
}
