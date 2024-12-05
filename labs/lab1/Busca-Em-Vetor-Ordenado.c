#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000

double timeInit, timedif;
void genNumbers(int* vNums);
void sortArray(int* vNums);
int* findDifferences(int* v1, int* v2, int* numDifferences);

int main(void) {
    srand(time(NULL));  

    timeInit = (double)clock() / CLOCKS_PER_SEC;

    int vNums[MAX], vNums2[MAX], * vdif;
    int numDifferences = 0;

    genNumbers(vNums);
    sortArray(vNums);
    printf("v1 \n\n");
    for (int i = 0; i < MAX; i++)
        printf("%d ", vNums[i]);
    genNumbers(vNums2);

    printf("\n\nv2 \n\n");
    for (int i = 0; i < MAX; i++)
        printf("%d ", vNums2[i]);


    vdif = findDifferences(vNums, vNums2, &numDifferences);

    if (vdif != NULL) {
        printf("\n\nNumeros nao encontrados em v1:\n");
        for (int i = 0; i < numDifferences; i++) {
            printf("%d ", vdif[i]);
        }
        printf("\n");
        free(vdif);  
    }
    else {
        printf("Erro de alocacao de memoria.\n");
    }

    timedif = (((double)clock()) / CLOCKS_PER_SEC) - timeInit;
    printf("\nTempo de execucao: %.2f segundos\n", timedif);

    return 0;
}

void genNumbers(int* vNums) {
    for (int i = 0; i < MAX; i++) {
        vNums[i] = rand() % MAX + 1;  
    }
}

void sortArray(int* vNums) {
    int i, j, temp;
    for (i = 0; i < MAX; ++i) {
        for (j = i + 1; j < MAX; ++j) {
            if (vNums[i] > vNums[j]) {
                temp = vNums[i];
                vNums[i] = vNums[j];
                vNums[j] = temp;
            }
        }
    }
}

int* findDifferences(int* v1, int* v2, int* numDifferences) {
    int* differences;
    int countDifferences = 0;

    for (int i = 0; i < MAX; i++) {
        int start = 0;
        int end = MAX - 1;
        int found = 0;

        while (start <= end) {
            int half = (start + end) / 2;

            if (v1[half] < v2[i]) {
                start = half + 1;
            }
            else if (v1[half] > v2[i]) {
                end = half - 1;
            }
            else {
                found = 1;
                break;
            }
        }

        if (!found) {
            countDifferences++;
        }
    }

    differences = (int*)malloc(countDifferences * sizeof(int));
    if (differences == NULL) {
        *numDifferences = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < MAX; i++) {
        int start = 0;
        int end = MAX - 1;
        int found = 0;

        while (start <= end) {
            int half = (start + end) / 2;

            if (v1[half] < v2[i]) {
                start = half + 1;
            }
            else if (v1[half] > v2[i]) {
                end = half - 1;
            }
            else {
                found = 1;
                break;
            }
        }

        if (!found) {
            differences[index++] = v2[i];
        }
    }

    *numDifferences = countDifferences;
    return differences;
}