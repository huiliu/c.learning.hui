#include <stdio.h>

void var_define();
void char_func();


int main(int argc, char **argv)
{
//  var_define();
    char_func();
    return 0;
}

void var_define()
{
    int id[4] = {1,2,3,4};
    int ie[9] = {1,2,3,4};
    // gcc Error
    //int ih[1,2,3,4];
    int ih[] = {1,2,3,4};
    int i;

    for (i = 0; i < 4; i++){
        printf("id[%d] = %d, ie[%d] = %d, ih[%d] = %d\n", i, id[i], \
 i, ie[i], i, ih[i]);
    }
}

void char_func()
{
    char stooge1[4];
    char stooge2[6];
    char stooge3[6] = "bamboo";

    stooge1[0] = 'L';
    stooge1[1] = 'i';
    stooge1[2] = 'u';
    stooge1[3] = '\0';

    printf("Please enter the second stooge's name: ");
    scanf("%s", stooge2);
    printf("%s size is %d\n", stooge1, (int)sizeof(stooge1));
    printf("%s size is %d\n", stooge2, (int)sizeof(stooge2));
    printf("%s size is %d\n", stooge3, (int)sizeof(stooge3));
}
