#include <stdio.h>

static int iCount = 0;

int bSearch(int key, int *array, int n)
{
    int i, low, high, mid;

    // the low and top index
    low = 0, high = n-1;

    for (i = 0; i < n; i++)
    {
        iCount++;
        fprintf(stdout, "%d\n", iCount);
        // get the middle index
        mid = (high + low) / 2;
        /*
                 low      mid         high
                  |        |           |
        index     0        3           7
                  |        |           |
        array     1, 2, 3, 4, 5, 6, 7, 8
         */
        if (array[mid] > key)
            high = mid - 1;
        else if (array[mid] < key)
            low = mid + 1;
        else
            return i;
    }

    return -1;
}

int main(int argc, char **argv)
{
    int A[] = {1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 ,36 ,37 ,38 ,39 ,40 ,41 ,42 ,43 ,44 ,45 ,46 ,47 ,48 ,49 ,50 ,51 ,52 ,53 ,54 ,55 ,56 ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,70 ,71 ,72 ,73 ,74 ,75 ,76 ,77 ,78 ,79 ,80 ,81 ,82 ,83 ,84 ,85 ,86 ,87 ,88 ,89 ,90 ,91 ,92 ,93 ,94 ,95 ,96 ,97 ,98 ,99 ,100};
    int i;

/*
    for (i = 13; i > 0; i--)
    {
        if (bSearch(i, A, 13) > -1)
            fprintf(stdout, "Find >>%d<<\n", i);
        else
            fprintf(stdout, "Doesn't find the number >>%d<<\n", i);
    }
    */

    bSearch(2, A, 100);
    return 0;
}
