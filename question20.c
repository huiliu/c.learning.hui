#include <stdio.h>
#include <string.h>


#define STUDENT_NUM     30
#define STR_LEN         30
#define COLUMN_COUNT    3

int readData(const char *fname, char Record[][COLUMN_COUNT][STR_LEN]);
int score(char Record[][COLUMN_COUNT][STR_LEN]);
int sort(char Record[][COLUMN_COUNT][STR_LEN]);
int class(char Record[][COLUMN_COUNT][STR_LEN]);
void output(int n, char item[][STR_LEN]);

int main(int argc, char **argv)
{
    char A[STUDENT_NUM][COLUMN_COUNT][STR_LEN];
    readData(argv[1], A);

    #ifdef DEBUG
    int i,j;
    for (i = 0; i < STUDENT_NUM; i++){
        for (j = 0; j < COLUMN_COUNT; j++){
            printf("%s\t", A[i][j]);
        }
        printf("\n");
    }
    #endif

    score(A);
    sort(A);
    class(A);
    return 0;
}

int readData(const char *fname, char Record[][COLUMN_COUNT][STR_LEN])
{
    FILE *fp;
    int i, j;

    if ((fp = fopen(fname, "r")) == NULL){
        printf("Open File Failed! Please Check It!\n");
        fclose(fp);
        return 1;
    }

    for (i = 0; i < STUDENT_NUM; i++){
        for (j = 0; j < COLUMN_COUNT - 1; j++){
            fscanf(fp, "%s", Record[i][j]);
        }
    }

    fclose(fp);
    return 0;
}

int score(char Record[][COLUMN_COUNT][STR_LEN])
{
    char correct[] = "FFTFTFTTTFFFTFTFFTFFTTFTT", tmp;
    int count = strlen(correct);
    int i, j, r;

    for (i = 0; i < STUDENT_NUM; i++){
        r = 0; 
        for (j =0; j < count; j++){
            if (strncmp(&correct[j], &Record[i][1][j], 1) == 0)
                r++;
        }
        tmp = (char)r;
        strcpy(Record[i][2], &tmp);
    }
    return 0;
}

int sort(char Record[][COLUMN_COUNT][STR_LEN])
{
    int i, j, k;
    char tmp[STR_LEN];

    for (i = 0; i < STUDENT_NUM; i++){
        for (j = 0; j < STUDENT_NUM; j++){
            if (strncmp(Record[i][2], Record[j][2], 1) < 0){
                for (k = 0; k < COLUMN_COUNT; k++){
                    strcpy(tmp, Record[i][k]);
                    strcpy(Record[i][k], Record[j][k]);
                    strcpy(Record[j][k], tmp);
                }
            }
        }
    }
    return 0;
}

int class(char Record[][COLUMN_COUNT][STR_LEN])
{
    int A = (int)(STUDENT_NUM * 0.1);
    int B = A + (int)(STUDENT_NUM * 0.9 * 0.15);
    int C = B + (int)(STUDENT_NUM * 0.9 * 0.85 * 0.5);
    int D = C + (int)(STUDENT_NUM * 0.9 * 0.85 * 0.5 * 0.15);
    int E = (int)(STUDENT_NUM * 0.9);
    int i = 0;

    for (i = 0; i < STUDENT_NUM; i++){
        if (i < A){
            printf("成绩为A的同学:\n");
            output(COLUMN_COUNT, Record[i]);
        }else if (i < B){
            printf("成绩为B的同学:\n");
            output(COLUMN_COUNT, Record[i]);
        }else if (i < C){
            printf("成绩为C的同学:\n");
            output(COLUMN_COUNT, Record[i]);
        }else if (i < D){
            printf("成绩为D的同学:\n");
            output(COLUMN_COUNT, Record[i]);
        }else if (i > E){
            printf("成绩为E的同学:\n");
            output(COLUMN_COUNT, Record[i]);
        }
    }
    return 0;
}

void output(int n, char item[][STR_LEN])
{
    int i;

    for (i = 0; i < n-1; i++)
        printf("%s\t", item[i]);
    printf("\n");
}
