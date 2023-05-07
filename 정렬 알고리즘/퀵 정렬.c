#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 8

int QuickSort(int arr[], int left, int right);

int main() {

    // 파일 열기 
    FILE* fp = NULL;
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
    // 정수 값을 저장할 배열 
    int arr[MAX];
    int i = 0;
    // 파일에서 정수배열 읽어오기  
    while (fscanf(fp, "%d", &arr[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

    // 퀵 정렬 함수 수행 
    QuickSort(arr, 0, MAX - 1);

    // 결과 저장할 텍스트 파일 
    fp = fopen("result.txt", "w");

    if (fp == NULL)
    {
        printf("파일을 여는데 실패했습니다.\n");
        return 1;
    }
    // 파일에 정렬된 결과를 쓴다. 
    for (i = 0; i < MAX; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);

    return 0;
}

// 퀵정렬 함수
int QuickSort(int arr[], int left, int right)
{
    srand(time(NULL));

    if (left >= right) return 1;
    // 피봇을 선정하기 위해 랜덤 값 k를 구한다. 
    int k = rand() % (right - left + 1) + left;

    int pivot = arr[k];  // 피봇을 선정 
    int tmp1, tmp2;
    // 배열의 첫 번째 원소와 피봇의 자리를 교환한다. 
    tmp1 = arr[left];
    arr[left] = arr[k];
    arr[k] = tmp1;

    int i = left + 1;
    int j = right;


    while (i < j)
    {
        while (i <= right && arr[i] <= pivot) { // pivot보다 작은 값을 찾을 때까지 i 증가 
            i++;
        }
        while (j > left && arr[j] >= pivot) // pivot보다 큰 값을 찾을 때까지 j 감소 
        {
            j--;
        }
        if (i > j)          // i가 j를 넘어간 경우 피봇과 arr[j]를 교환 
        {
            tmp2 = arr[left];
            arr[left] = arr[j];
            arr[j] = tmp2;
        }
        else				// i가 j보다 작을 경우  
        {
            tmp2 = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp2;
        }
    }

    // pivot을 기준으로 왼쪽 부분배열과 오른쪽 부분배열에 대해 재귀호출 
    QuickSort(arr, left, j - 1);
    QuickSort(arr, j + 1, right);
    return 0;
}
