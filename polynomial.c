#include <stdio.h>
#include <stdlib.h>

//#define DEBUG
#define POLY_LEN    3
typedef struct {
    float coef;
    int expon;
} polynomial;

void initPoly(polynomial *p , float c, int e);
void outputPoly(polynomial *p, int n);
int isZero(polynomial *a);
float getCoef(polynomial *a, int expon);
int getMaxExpon(polynomial *a);
polynomial *attatch(polynomial *a, int *p, float c, int e);
polynomial *Remove(polynomial *p, int *l, int e);
polynomial *singleMult(polynomial *p, int *l, float c, int e);
polynomial *Add(polynomial *p1, int *m, polynomial *p2, int n);
polynomial *Mult(polynomial *p1, int *m, polynomial *p2, int *n, int *);

int main(int argc, char **argv)
{
    int da = 3;
    int db = 3;
    polynomial A[5], B[5];
    polynomial *C;

    initPoly(A, 2.0, 1000);
    initPoly(A+1, 1.0, 4);
    initPoly(A+2, 1.0, 0);

    initPoly(B, 10.0, 3);
    initPoly(B+1, 3.0, 2);
    initPoly(B+2, 1.0, 0);

    outputPoly(A, da);
    outputPoly(B, db);

    // 演示GET
    printf("The Max Exponent in A is %d\n", getMaxExpon(A));
    printf("The Max Exponent in B is %d\n", getMaxExpon(B));
    printf("The coef of Exponent %d in A is %f\n", 4, getCoef(A, 4));
    printf("The coef of Exponent %d in A is %f\n",2, getCoef(B, 2));

    
    int mult = 0;
    C = Mult(A, &da, B, &db, &mult);
    outputPoly(C, mult);
/*
    attatch(A, &da, 4, 5);

    Add(A, &da, B, db);
    outputPoly(A, da);

    singleMult(A, &da, 2, 3);
    outputPoly(A, da);

    Remove(A, &da, 4);
    outputPoly(A, da);
    Remove(B, &db, 2);
    outputPoly(B, db);
*/
    return 0;
}

void initPoly(polynomial *p , float c, int e)
{
    p->coef = c;
    p->expon = e;
}

void outputPoly(polynomial *p, int n)
{
    int i;
    static int c = 0;
    printf("第%d个多项式为:\n", c++);
    for (i = 0; i < n; i++) {
        printf("Coef %d = %f, expon = %d\n", i, p->coef, p->expon);
        p++;
    }
}

// 判断一个多项式是否为零
int isZero(polynomial *a)
{
    int i;
    for (i = 0; i < POLY_LEN; i++) {
        if (a->coef != 0 && a->expon != 0)
            return 1;
        a++;
    }
    return 0;
}

float getCoef(polynomial *a, int expon)
{
    int i;
    for (i = 0; i < POLY_LEN; i++) {
        if (a->expon == expon)
            return a->coef;
        a++;
    }
    return 0;
}

int getMaxExpon(polynomial *a)
{
    int i, n = 0;
    for (i = 0; i < POLY_LEN; i++) {
        if (a->expon > n)
            n = a->expon;
        a++;
    }
    return n;
}

polynomial *attatch(polynomial *a, int *p, float c, int e)
{
    (a + *p)->coef = c;
    (a + *p)->expon = e;
    (*p)++;
    return a;
}

polynomial *Remove(polynomial *p, int *l, int e)
{
    int i, state = 0;
    for (i = 0; i < *l; i++) {
        #ifdef DEBUG
        printf("Remove %d\t%f\t%d\n", i, p[i].coef, p[i].expon);
        #endif
        if (state == 0){
            if (p[i].expon == e){
                #ifdef DEBUG
                printf("Remove %d\n", i);
                #endif
                state = 1;
            }
        }else if (state == 1) {
            if (i < *l) {
                p[i-1] = p[i];
            }else{
                p[i].coef = 0;
                p[i].expon = 0;
            }
        }
    }
    if (state == 1)
        (*l)--;
    return p;    
}

polynomial * singleMult(polynomial *p, int *l, float c, int e)
{
    int i;
    for (i = 0; i < *l; i++) {
        p->coef *= c;
        p->expon += e;
        p++;
    }
    return p;
}

polynomial *Add(polynomial *p1, int *m, polynomial *p2, int n)
{
    int i, j;
    polynomial *tmp;
    tmp = p1;

    for (j = 0; j < n; j++) {
        for (i = 0; i < *m; i++) {
            #ifdef DEBUG
            printf("j = %d  %d\ti = %d %d\n", j, p2[j].expon, i, tmp[i].expon);
            #endif
            if (p2[j].expon == tmp[i].expon) {
                tmp[i].coef += p2[j].coef;
                break;
            }
            //tmp++;
        }
        #ifdef DEBUG
        printf("i = %d\tm = %d\n", i , *m);
        #endif
        if (i == *m){
            attatch(p1, m, p2[j].coef, p2[j].expon);
        }
        //p2++;
    }
    return p1;
}


polynomial *Mult(polynomial *p1, int *m, polynomial *p2, int *n, int *f)
{
    int i, j, k, c;
    polynomial *pr, *tmp;
    pr = malloc(sizeof(polynomial)*(*m)*(*n));
    tmp = malloc(sizeof(polynomial));
    c = 0;
    for (i = 0; i < *m; i++) {
        for (j = 0; j < *n; j++) {
            tmp->expon = p1->expon + p2[j].expon;
            tmp->coef = p1->coef * p2[j].coef;
            // 不能使用指针是因为嵌套循环让指针跑越界了
            // 所以内层最好不要使用指针
            //p2++;
        #ifdef DEBUG
        printf("j = %d\tcoef = %f\texpon = %d\n", j, tmp->coef, tmp->expon);
        #endif
            for (k = 0; k < c; k++) {
                if (pr[k].expon == tmp->expon) {
                    pr[k].coef += tmp->coef;
                    break;
                }
            }
        //#ifdef DEBUG
        //printf("c = %d\tk = %d\n", c , k);
        //#endif
            if (k == c)
                attatch(pr, &c, tmp->coef, tmp->expon);
        }
        // 而外层则可以 
        p1++;
    }
    free(tmp);
    *f = c;
    return pr;
}
