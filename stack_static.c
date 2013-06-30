/*
 * 此程序主要演示了栈的一些基本操作，如判断是否为空，
 * 是否已满，压栈，弹出等
 *
 * 其中栈是用一维数组静态表示的，也可以通过malloc,
 * realloc来动态操作
 *
 * Date: Tue Jun 19 19:49:55 CST 2012
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG
#define MAX_STACK   100

typedef struct {
    int item;
}Element;

int top = -1;

int isEmpty(Element *stack)
{
    if (top < 0)
        return 1;
    else
        return 0;
}

int isFull(Element *stack)
{
    if (top >= MAX_STACK - 1)
        return 1;
    else
        return 0;
}

int Push(Element *stack, int item)
{
    if (isFull(stack))
        return 0;
    else
        stack[++top].item = item;
    return 1;
}

Element Pop(Element *stack)
{
    if (isEmpty(stack))
        exit(EXIT_FAILURE);
    else
        return stack[top--];
}

int RandNumber(int range)
{
    srand(time(NULL));
    return rand() % range;
}

void Print(Element *stack)
{
    int i;
    for (i = 0; i <= top; i++)
        printf("i = %d\t%d\n", i, stack[i].item);
}

int main(int argc, char **argv)
{
    Element stack[MAX_STACK];
    int i;
    for (i = 0; i < 10; i++) {
        Push(stack, RandNumber(i+5));
    }
    #ifdef DEBUG
    printf("top = %d\n", top);
    #endif

    Print(stack);
    
    printf("\nTest Pop operation: %d\n", Pop(stack).item);
    return 0;
}
