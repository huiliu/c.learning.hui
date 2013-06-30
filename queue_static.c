/*
 * 演示了队列的一些的操作，这个队列是通过一维数组实现
 * 循环队列。
 
 * 其中front指向的是队列前的一个空位，所以整个队列中的
 * 元素应该比队列的最大元素数少一个。
 *
 * 其中有一些语句比较巧妙，但难以理解
 *
 * Date: Tue Jun 19 20:58:28 CST 2012
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#define DEBUG
#define MAX_QUEUE_SIZE  20
typedef struct {
    int key;
}Element;

int rear = -1, front = -1;

int isFull();
int isEmpty();
int Add(Element *q, Element item);
Element Pop(Element *q);

int main(int argc, char **argv)
{
    Element q[MAX_QUEUE_SIZE];
    int i;
    Element tmp;
    srand(time(NULL));
    for (i = 0; i < MAX_QUEUE_SIZE - 1; i++) {
        tmp.key = rand() % 13;
        if (!Add(q, tmp))
            printf("插入队列出错！\n");
    }

    for (i = 0; i < MAX_QUEUE_SIZE ; i++) {
        printf("i = %d\t%d\n", i, Pop(q).key);
    }
    
    return 0;    
}

int isFull()
{
    if (rear >= MAX_QUEUE_SIZE -1) {
        #ifdef DEBUG
        printf("%d, %d\n", rear, MAX_QUEUE_SIZE -1);
        #endif
        printf("队列满！\n");
        return 1;
    }else
        return 0;
}

int isEmpty()
{
    if (rear == front) {
        #ifdef DEBUG
        printf("%d, %d\n", rear, front);
        #endif
        printf("队列为空！\n");
        return 1;
    }else
        return 0;
}

// 增加元素
int Add(Element *q, Element item)
{
    // 使用循环队列 
    /*
     * 便于理解的传统写法
     * if (rear == MAX_QUEUE_SIZE -1) rear = 0;
     * else rear ++
     *
     */
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if(!isFull()) {
        q[rear] = item;
        return 1;
    }else
        return 0;
}

// 弹出元素
Element Pop(Element *q)
{
    if (!isEmpty()) {
    // 使用循环队列 
    /*
     * 便于理解的传统写法
     * if (rear == MAX_QUEUE_SIZE -1) rear = 0;
     * else rear ++
     *
     */
        front = (front + 1) % MAX_QUEUE_SIZE;
        return q[front];
    }else
        exit(EXIT_FAILURE);
}

void Print(Element *q)
{

}
