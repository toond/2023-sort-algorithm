#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 8

void mergeSort(int data[], int p, int r);
void merge(int data[], int p, int q, int r);

int main() {

    int data[MAX];
    int i = 0;
    FILE* fp = NULL;
    // 파일 열어서 읽기 
    fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("파일을 여는데 실패했습니다. \n");
        return 1;
    }
    else
    {
        printf("파일을 여는데 성공했습니다. \n");
    }

    // 파일에서 정수를 읽어와 data 배열에 저장한다. 
    while (fscanf(fp, "%d", &data[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

    printf("정렬 전\n");
    for (i = 0; i < MAX; i++) {
        printf("%d ", data[i]);
    }
    // 합병 정렬 수행 
    mergeSort(data, 0, MAX - 1);

    // 수행한 결과를 파일에 쓴다. 
    fp = fopen("result.txt", "w");

    for (i = 0; i < MAX; i++) {
        fprintf(fp, "%d ", data[i]);
    }

    printf("\n정렬 후\n");
    for (i = 0; i < MAX; i++) {
        printf("%d ", data[i]);
    }

    return 0;
}

void mergeSort(int data[], int p, int r) {

    int q;

    if (p < r) {
        // p와 r의 중간 인덱스 
        q = (p + r) / 2;
        mergeSort(data, p, q);
        mergeSort(data, q + 1, r);
        merge(data, p, q, r);
    }
}
void merge(int data[], int p, int q, int r) {

    int i = p, j = q + 1, k = p;
    int tmp[8]; // 임시 배열 
    int a;

    // data[i]와 data[j]를 비교해 작은 값을 먼저 tmp 배열에 저장한다. 
    while (i <= q && j <= r) {
        if (data[i] <= data[j]) tmp[k++] = data[i++];
        else tmp[k++] = data[j++];
    }
    // i가 q까지 가지 못했을 경우 
    while (i <= q) tmp[k++] = data[i++];
    // j가 r까지 가지 못했을 경우 
    while (j <= r) tmp[k++] = data[j++];

    // 임시배열의 값을 원래배열에 저장한다. 
    for (a = p; a <= r; a++) data[a] = tmp[a];
}