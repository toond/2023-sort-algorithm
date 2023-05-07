#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 8

int main()
{
    FILE* fp = NULL;
    fp = fopen("data.txt", "r");
    int result;			// k 번째로 작은 값 
    int num;			// k 번째 
    if (fp == NULL)
    {
        printf("파일을 여는데 실패했습니다. \n");
        return 1;
    }
    else
    {
        printf("파일을 여는데 성공했습니다. \n");
    }
    int arr[MAX];
    int i = 0;
    // 파일에서 배열 읽어오기  
    while (fscanf(fp, "%d", &arr[i]) != EOF)
    {
        i++;
    }
    fclose(fp);
    printf("몇 번째로 작은 값을 원하십니까? ");
    scanf("%d", &num);

    // 선택 문제 함수 수행 
    result = Selection(arr, 0, MAX - 1, num);

    // 결과 저장 
    fp = fopen("result.txt", "w");

    if (fp == NULL)
    {
        printf("파일을 여는데 실패했습니다.\n");
        return 1;
    }

    fprintf(fp, "%d ", result);
    printf("%d번재로 작은 값은 %d입니다", num, result);
    fclose(fp);
    return 0;
}

int Selection(int arr[], int left, int right, int k)
{


    srand(time(NULL));
    // 피봇을 선정하기 위해 랜덤 값 p를 구한다.
    int p = rand() % (right - left + 1) + left;

    int pivot = arr[p];     // 피봇을 선정

    int i = left + 1;       // pivot보다 작은 값들을 왼쪽에 저장하기 위한 배열의 인덱스 
    int j = right;          // pivot보다 큰 값들을 오른쪽애 저장하기 위한 배열의 인덱스

    int tmp1, tmp2;
    // 피봇과 첫 번째 원소의 자리를 교환한다. 
    tmp1 = arr[left];
    arr[left] = arr[p];
    arr[p] = tmp1;
    int S;
    while (i < j)
    {
        while (i <= right && arr[i] <= pivot) // pivot보다 작은 값을 찾을 때까지 i 증가
        {
            i++;
        }
        while (j > left && arr[j] >= pivot)  // pivot보다 큰 값을 찾을 때까지 j 감소
        {
            j--;
        }
        if (i > j)    // i가 j를 넘어간 경우 피봇과 arr[j]를 교환 
        {
            tmp2 = arr[left];
            arr[left] = arr[j];
            arr[j] = tmp2;
        }
        else		  // i가 j보다 작을 경우
        {
            tmp2 = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp2;
        }
    }

    // Small 그룹의 크기 
    S = (j - 1) - left + 1;
    // Small 그룹에서 다시 찾는다. 
    if (k <= S) {
        Selection(arr, left, j - 1, k);
    }
    // k 번재로 작은 숫자 반환 
    else if (k = S + 1) {
        return arr[j];
    }
    // large 그룹에서 찾는다. 
    else {
        Selection(arr, j + 1, right, k - S - 1);
    }
}