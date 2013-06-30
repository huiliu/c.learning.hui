/*
 *
 * 永远不要相信用户输入的数据
 * 注意数组防止越界
 *
 *
 * 问题：
 *
 * 如果是比较单个字符是否相等，需要使用strncmp(a, b, 1)
 * 如果同时对打开两个文件进行if检测，有一个文件会打开失败，且不会提示
 *
 *
 * TODO:
 *  修正question24加密解密算法中的BUG，并使用状态机重新实现
*/


#include <stdio.h>
#include <string.h>

//#define DEBUG
#define MATRIX_MAX  100

void outputMatrix(int n, int A[][MATRIX_MAX]);
void question01(void);
void question02(void);
int question21_main(void);
void question21_add(int n, int A[][MATRIX_MAX], int B[][MATRIX_MAX], int C[][MATRIX_MAX]);
void question21_sub(int n, int A[][MATRIX_MAX], int B[][MATRIX_MAX], int C[][MATRIX_MAX]);
void question21_mul(int n, int A[][MATRIX_MAX], int B[][MATRIX_MAX], int C[][MATRIX_MAX]);
void question21_inv(int n, int A[][MATRIX_MAX]);
void question21_trans(int n, int A[][MATRIX_MAX]);
void question22(void);

void question23_main(void);
int question23_prime(int n);
void question24(void);

int main(int argc, char **argv)
{
    //question01();
    //question02();
    //question21_main();
    //question22();
    //question23_main();
    question24();
    return 0;
}

void question01(void)
{
    // 使用整型变量会越界
    float numbs[100] = {1, 3, 5};
    int i, j;

    for (i = 3; i < 100; i++){
        numbs[i] = 0;
        for (j = 0; j < i; j++)
            numbs[i] += numbs[j];
    }
    for (i = 0; i < 100; i++)
        printf("numbs[%d] = %f\t", i, numbs[i]);

}

void question02(void)
{
    char H[6][10] = {
                        {' ', ' ', 'H', ' ', ' ', ' ', ' ', 'H', ' ', ' '},
                        {' ', ' ', 'H', ' ', ' ', ' ', ' ', 'H', ' ', ' '},
                        {' ', ' ', 'H', 'H', 'H', 'H', 'H', 'H', ' ', ' '},
                        {' ', ' ', 'H', ' ', ' ', ' ', ' ', 'H', ' ', ' '},
                        {' ', ' ', 'H', ' ', ' ', ' ', ' ', 'H', ' ', ' '},
                        {' ', ' ', 'H', ' ', ' ', ' ', ' ', 'H', ' ', ' '}
                    };
    char U[6][10] = {
                        {' ', ' ', 'U', ' ', ' ', ' ', ' ', 'U', ' ', ' '},
                        {' ', ' ', 'U', ' ', ' ', ' ', ' ', 'U', ' ', ' '},
                        {' ', ' ', 'U', ' ', ' ', ' ', ' ', 'U', ' ', ' '},
                        {' ', ' ', 'U', ' ', ' ', ' ', ' ', 'U', ' ', ' '},
                        {' ', ' ', 'U', ' ', ' ', ' ', ' ', 'U', ' ', ' '},
                        {' ', ' ', ' ', 'U', 'U', 'U', 'U', 'U', ' ', ' '}
                    };
    char I[6][10] = {
                        {' ', ' ', 'I', 'I', 'I', 'I', 'I', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', 'I', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', 'I', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', 'I', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', 'I', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', 'I', 'I', 'I', 'I', 'I', ' ', ' ', ' '}
                    };

    int i, j;

    for (i = 0; i < 6; i++){
        for (j = 0; j < 10; j++)
            printf("%c", H[i][j]);
        for (j = 0; j < 10; j++)
            printf("%c", U[i][j]);
        for (j = 0; j < 10; j++)
            printf("%c", I[i][j]);
        printf("\n");
    }

}

int question21_main(void)
{
    //
    // 要求用户输出矩阵的维数
    // 进入矩阵运算菜单，同时可以重新选择矩阵维数和退出程序
    //
    char *menu1 = "Please enter the demension of matrix: ";
    char *menu = "1. Add\n2. Subtract\n3. Multiply\n4. Invert\n5. Transpose\n6. Reset Dimension\n7. Quit\n";
    int n, state;
    int i, j;
    int A[MATRIX_MAX][MATRIX_MAX], B[MATRIX_MAX][MATRIX_MAX], C[MATRIX_MAX][MATRIX_MAX];

    printf(menu1);
    scanf("%d", &n);

    while (1){
        printf(menu);
        scanf("%d", &state);

        if (state == 1 || state == 2 || state == 3 || state == 4 || state == 5){
            printf("请输入矩阵元: \n");
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                    scanf("%d", &A[i][j]);
            if (state == 1 || state == 2 || state == 3){
                printf("请输入第二个矩阵的矩阵元: \n");
                for (i = 0; i < n; i++)
                    for (j = 0; j < n; j++)
                        scanf("%d", &B[i][j]);
                // 进行运算
                if (state == 1)
                    question21_add(n, A, B, C);
                else if (state == 2)
                    question21_sub(n, A, B, C);
                else if (state == 3)
                    question21_mul(n, A, B, C);
                outputMatrix(n, C);
            }else if (state == 4){
                question21_inv(n, A);
                outputMatrix(n, A);
            }else{
                question21_trans(n, A);
                outputMatrix(n, A);
            }
        }else if (state == 6){
                printf(menu1);
                scanf("%d", &n);
        }else if (state == 7){
                printf("Good Bye!\n");
                return 0;
        }else{
                printf("Input Error, Please try again!\n");
                continue;
        }

    }

}

void outputMatrix(int n, int A[][MATRIX_MAX])
{
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            printf("%d\t", A[i][j]);
        printf("\n");
    }
}

void question21_add(int n, int A[][MATRIX_MAX], int B[][MATRIX_MAX], int C[][MATRIX_MAX])
{
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void question21_sub(int n, int A[][MATRIX_MAX], int B[][MATRIX_MAX], int C[][MATRIX_MAX])
{
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void question21_mul(int n, int A[][MATRIX_MAX], int B[][MATRIX_MAX], int C[][MATRIX_MAX])
{
    int i, j, k;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            C[i][j] = 0;
            for (k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void question21_inv(int n, int A[][MATRIX_MAX])
{
    int i, j;
    int tmp;
    for (i = 0; i < n/2; i++){
        for (j = 0; j < n; j++){
        tmp = A[i][j];
        A[i][j] = A[n-i-1][j];
        A[n-i-1][j] = tmp;
        }
    }
}

void question21_trans(int n, int A[][MATRIX_MAX])
{
    int i, j;
    int tmp;
    printf("Transport:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < i; j++){
            tmp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = tmp;
        }
    }
}

void question22(void)
{
    FILE *pf;
    char *fname = "test/question22";
    char wordlist[1000][20], str[20];
    int wordcount[1000];
    int cur = 0;

    if ((pf = fopen(fname, "r")) == NULL){
        printf("Failed to open the file %s", fname);
        fclose(pf);
    }else{
        fscanf(pf, "%s", str);
        strcpy(wordlist[0], str);
        #ifdef DEBUG
        printf("%s $\n", wordlist[0]);
        #endif
        wordcount[0] = 1;
        while (fscanf(pf, "%s", str) != EOF){
            int i = 0;
            // 特别注意标量的增加
            cur++;
            for (i = 0; i < cur; i++){
                if (strcmp(wordlist[i], str) == 0){
                    wordcount[i]++;
                    break;
                }
            }
            if (i == cur){
                strcpy(wordlist[i], str);
                wordcount[i] = 1;
            }
            #ifdef DEBUG
            printf("%d = %s $\n",i, wordlist[i]);
            #endif
        }
    }
    int i, j;
    for (i = 0; i < 200; i++){
        j += wordcount[i];
        printf("%s = %d\t", wordlist[i], wordcount[i]);
        if (i % 10 == 0)    printf("\n");
    }
    printf("\nWord count is %d\n", j);
}

void question23_main(void)
{
    int i, ii = 0, x;
    printf("Please enter a positive even number: ");
    scanf("%d", &x);
    if (x < 0)
        printf("Input error! Please enter a positive even number: ");
    else{
        for (i = 1; i <= x/2; i++){
            if (question23_prime(i) == 1 && question23_prime(x - i)){
                ii++;
                printf("%d = %d + %d\n", x, i, x-i);
            }
        }
        if (ii == 0)
            printf("%d cann't be decompostion the sum of two prime number\n", x);
    }
}

int question23_prime(int n)
{
    int i;
    for (i = 2; i < n; i++){
        if (n %i == 0)
            // 不是素数
            return 0;
    }
    // 是素数
    return 1;
}

#define PWD_TABLE_LEN   95
#define FILE_NAME_LEN   10
#define PASSWD_LEN      64
#define ONCE_TEXT_LEN   4096

void question24(void)
{
    int i, j, m, n;
    char pwd_table[PWD_TABLE_LEN][PWD_TABLE_LEN];

    // 生成密码表
    for (i = 0; i < PWD_TABLE_LEN; i++){
        for (j = 0; j < PWD_TABLE_LEN; j++){
            pwd_table[i][j] = (char)0;
            n = 32 + j + i;
            if (n > 126)    n = n -126 + 31;
            pwd_table[i][j] = (char)n;
            #ifdef DEBUG
            printf("%d,%d = %d, %c ",i, j, n, pwd_table[i][j]);
            #endif
        }
        #ifdef DEBUG
        printf("\n");
        #endif
    }

    int state, pwd_len;
    char password[64], ifname[10], ofname[10], text[4096];
    FILE *ifp, *ofp;

    printf("\n1. 加密文件\n2. 加密字符串\n3.解密文件\n4.解密字符\n");
    scanf("%d", &state);

    if (state == 1){
    // 加密文件内容
        printf("Please enter password: ");
        scanf("%s", password);
        pwd_len = strlen(password);

        printf("Please enter the input file name: ");
        scanf("%s", ifname);
        printf("Please enter the output file name: ");
        scanf("%s", ofname);

        // Check the input data by user
        if (strlen(ifname) > 10 || strlen(ofname) >10){
            printf("The length of file name exceed limits(10)\n");
        }

        //  为什么同时对打开两个文件进行测试会出错
        if ((ofp = fopen(ofname, "a")) == NULL){
            printf("Failed to open the output file. Please Check it.");
            fclose(ofp);
        }
        if ((ifp = fopen(ifname, "r")) == NULL){
            printf("Failed to open the file(input or output). Please Check it.");
            fclose(ifp);
        }else{
            //while (fscanf(ifp, "%s", text) != EOF){
            while (fgets(text, 4096, ifp) != NULL){
                for (i = 0; i < strlen(text); i++){
                    // 换行符转换为int 为10, 减去32会为负值
                    m = (int)text[i] - 32;
                    n = (int)password[i % pwd_len] - 32;
                    #ifdef DEBUG
                    if (n < 0)
                        printf("%c%d,%d=%c ",text[i], m,n,(char)0);
                    else
                        printf("%c%d,%d=%c ",text[i], m,n,pwd_table[m][n]);
                    #endif

                    /*
                     *  此处不知道是不是有输出效率问题，一个字符一个字符的向文
                     *  件写入,效率应该比一次写入多个字符要低
                     *
                     *  TODO:   分块块写入文件
                    */
                    if (n < 0){
                        fputc((char)0, ofp);
                    }else{
                        fputc(pwd_table[m][n], ofp);
                    }
                }
            }
            fclose(ofp);
            fclose(ifp);
        }
    }else if (state == 2){
        printf("Please enter password: ");
        scanf("%s", password);
        pwd_len = strlen(password);

        printf("Please enter the text( < 4096): ");
        scanf("%s", text);

        printf("密文为:\n");
        for (i = 0; i < strlen(text); i++){
            m = (int)text[i] - 32;
            n = (int)password[i % pwd_len] - 32;
            if (n < 0){
                printf("%c", (char)0);
            }else{
                printf("%c", pwd_table[m][n]);
            }
        }
        printf("\n");
    }else if( state == 3 ){
        printf("請输入需要解密的文件名: ");
        scanf("%s", ifname);

        printf("Please enter password: ");
        scanf("%s", password);
        pwd_len = strlen(password);

        if ((ifp = fopen(ifname, "r")) == NULL){
            printf("Failed to open the file. Please Check it.");
            fclose(ifp);
        }

        char tmp = '\0';
        //while (fgets(text, 4096, ifp) != NULL){
        while (fscanf(ifp, "%s", text) != EOF){
            for (i = 0; i < strlen(text); i++){
                n = (int)password[i % pwd_len] - 32;
                //printf("'%c'", text[i]);
                if (strncmp(&text[i], &tmp, 1) == 0){
                    printf("\n");
                    continue;
                }
                for (j = 0; j < PWD_TABLE_LEN; j++){
                    if (strncmp(&text[i], &pwd_table[j][n], 1) == 0){
                        printf("%c", (char)(j + 32));
                        break;
                    }
                }
            }
        }
    }else if( state == 4 ){
        printf("請输入需要解密的字符串:(<4096) ");
        scanf("%s", text);

        printf("請输入密码: ");
        scanf("%s", password);
        pwd_len = strlen(password);

        for (i = 0; i < strlen(text); i++){
            n = (int)password[i % pwd_len] - 32;
            for (j = 0; j < PWD_TABLE_LEN; j++){
                if (strncmp(&text[i], &pwd_table[j][n], 1) == 0){
                    printf("%c", (char)(j + 32));
                    break;
                }
            }
        }
    }else{
        printf("Input Error! Please check it.\n");
    }
}
