/*
 * 对单向队列进行了一些修改，现在的队列可以双向插入
 * 双向删除,其它与之前的单向队列一样
 * 
 * 其中front指向的是队列前的一个空位，所以整个队列中的
 * 元素应该比队列的最大元素数少一个。
 *
 * 另外，增加了一个Print 函数用于打印队列
 *
 * 其中有一些语句比较巧妙，但难以理解
 *
 * Date: Tue Jun 19 20:58:28 CST 2012
 * Revision Date: Tue Jun 19 23:04:21 CST 2012
 *
 *
 *
 * 加入一个新函数anywhereAdd(...)可以在队列的任何位置插入元素
 *
 * Revision Date: Thu Jun 21 20:42:11 CST 2012
 *
 *
 *
 * 加入新函数anywherePop(...)可以在队列任何位置删除元素
 *
 * Revision Date: Thu Jun 21 21:16:29 CST 2012
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#define DEBUG
//#define DEBUG_DEEP_PRINT
#define MAX_QUEUE_SIZE  20
typedef struct {
    int key;
}Element;

int rear = -1, front = -1;

void initQueue(Element *q, int count, int flags);
int isFull();
int isEmpty();
int Add(Element *q, Element item, int flags);
int anywhereAdd(Element *q, Element item, int n);
Element Pop(Element *q, int flags);
Element anywherePop(Element *q, int n);
void Print(Element *q);

int main(int argc, char **argv)
{
    Element q[MAX_QUEUE_SIZE];
    Element tmp;

    initQueue(q, 5, 1);
    #ifdef DEBUG
    printf("Final rear = %d\n", rear);
    #endif
    // 用于测试Add和Pop
    tmp.key = 1000;
    initQueue(q, 5, 0);
    Print(q);

    /*
    // 测试在任何位置删除元素
    printf("Test Pop %d\t%d\n", 1, anywherePop(q, 0).key);
    Print(q);
    */

    /*
    anywhereAdd(q, tmp, 2);
    Print(q);
    */
/*
    Pop(q, 1);
    Print(q);

    Pop(q, 0);
    Print(q);
*/
    // 当rear > front时在任何位置插入数据
    /*
    tmp.key = 1000;
    anywhereAdd(q, tmp, 2);
    Print(q);
    anywhereAdd(q, tmp, 17);
    Print(q);
    */
    return 0;    
}

void initQueue(Element *q, int count, int flags)
{
    int i;
    Element tmp;
    srand(time(NULL));
    for (i = 0; i < count; i++) {
        tmp.key = rand() % 13;
        if (!Add(q, tmp, flags))
            printf("插入队列出错！\n");
    }
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
int Add(Element *q, Element item, int flags)
{
    // 使用循环队列 
    /*
     * 便于理解的传统写法
     * if (rear == MAX_QUEUE_SIZE -1) rear = 0;
     * else rear ++
     *
     */
    if(!isFull()) {
        if (flags == 1) {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            q[rear] = item;
        }else if (flags == 0) {
            #ifdef DEBUG
            printf("从头部插入...\n");
            printf("当前头部为：%d\n", front);
            printf("当前头部值为：%d\n", q[front+1].key);
            #endif
            if (--front < 0)
                front += MAX_QUEUE_SIZE;
            // 注意front为应该为一个空项
            q[front+1]= item;
            #ifdef DEBUG
            printf("传递来的值为：%d\n", item.key);
            printf("插入后头部为：%d\n", front);
            printf("当前头部值为：%d\n", q[front+1].key);
            #endif
        }else {
            printf("Add flags 设定错误!\n");
            exit(EXIT_FAILURE);
        }
        #ifdef DEBUG
        printf("rear = %d\t", rear);
        #endif
        return 1;
    }else
        return 0;
}

// 在n个位置增加元素
int anywhereAdd(Element *q, Element item, int n)
{
    // 可以在任何位置插入的循环队列 

    int x, i, m;

    if(!isFull()) {
        x = rear - front;
        if (x > 0 && n > front && n < rear) {
            for (i = rear; i >= n; i--)
                q[i+1] = q[i];
            q[n] = item;
            rear = (rear + 1) % MAX_QUEUE_SIZE;
        } else if (x < 0) {
            if ( front < n && n <MAX_QUEUE_SIZE) {
            // 此应该好好再想一下，有没有更好的方法
                for (i = rear + 1; i > 0; i--)
                    q[i] = q[i-1];
                q[0] = q[MAX_QUEUE_SIZE - 1];
                for (i = MAX_QUEUE_SIZE-1; i > n; i--)
                    q[i] = q[i-1];
            }else if (n >= 0 && n <= rear) {
                m = rear - n;
                for (i = rear + 1; i > n; i--)
                    q[i] = q[i-1];
            }
            q[n] = item;
            rear++;
        }
        return 1;
    }else
        return 0;
}

Element anywherePop(Element *q, int n)
{
    int x, i;
    Element tmp;
    tmp = q[n];
    x = rear - front;
    if (x > 0) {
        for (i = n; i < rear; i++)
            q[i] = q[i+1];
    }else if (x < 0) {
        if (n < rear) {
            for (i = n; i <rear; i++)
                q[i] = q[i+1];
        }else if (n > front && n < MAX_QUEUE_SIZE) {
            for (i = n; i < MAX_QUEUE_SIZE-1; i++)
                q[i] = q[i+1];
            q[i] = q[0];
            for (i = 0; i < rear; i++)
                q[i] = q[i+1];
        }
    }
    rear--;
    return tmp;
}
// 弹出元素
Element Pop(Element *q, int flags)
{
    if (!isEmpty()) {
    // 使用循环队列 
    /*
     * 便于理解的传统写法
     * if (rear == MAX_QUEUE_SIZE -1) rear = 0;
     * else rear ++
     *
     */
        if (flags == 1) {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return q[front];
        }else if (flags == 0) {
            Element tmp = q[rear];
            if (--rear < 0)
                rear += MAX_QUEUE_SIZE;
            return tmp;
        }else {
            printf("Pop flags 设定错误!\n");
            exit(EXIT_FAILURE);
        }
    }else
        exit(EXIT_FAILURE);
}

void Print(Element *q)
{
    static int m = 0;
    int n = rear - front;
    int i, ii;
    printf("第%d个队列为：\n", ++m);
    if (n > 0) {
        for (i = front + 1; i <= rear; i++) {
            printf("i = %d\t%d\n", i, q[i].key);
        }
    }else{
        for (i = 0; i < MAX_QUEUE_SIZE + n; i++) {
            ii = front + i + 1;
            #ifdef DEBUG_DEEP_PRINT
            printf("调试打印：i = %d\tn = %d\n", i, n);
            #endif
            if (ii < MAX_QUEUE_SIZE)
                printf("i = %d\t%d\n", ii, q[ii].key);
            else
                printf("i = %d\t%d\n", ii - MAX_QUEUE_SIZE, q[ii-MAX_QUEUE_SIZE].key);
        }
    }
}
