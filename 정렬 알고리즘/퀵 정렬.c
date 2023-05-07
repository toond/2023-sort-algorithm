#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 8

int QuickSort(int arr[], int left, int right);

int main() {

    // ���� ���� 
    FILE* fp = NULL;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("������ ���µ� �����߽��ϴ�. \n");
        return 1;
    }
    else
    {
        printf("������ ���µ� �����߽��ϴ�. \n");
    }
    // ���� ���� ������ �迭 
    int arr[MAX];
    int i = 0;
    // ���Ͽ��� �����迭 �о����  
    while (fscanf(fp, "%d", &arr[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

    // �� ���� �Լ� ���� 
    QuickSort(arr, 0, MAX - 1);

    // ��� ������ �ؽ�Ʈ ���� 
    fp = fopen("result.txt", "w");

    if (fp == NULL)
    {
        printf("������ ���µ� �����߽��ϴ�.\n");
        return 1;
    }
    // ���Ͽ� ���ĵ� ����� ����. 
    for (i = 0; i < MAX; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);

    return 0;
}

// ������ �Լ�
int QuickSort(int arr[], int left, int right)
{
    srand(time(NULL));

    if (left >= right) return 1;
    // �Ǻ��� �����ϱ� ���� ���� �� k�� ���Ѵ�. 
    int k = rand() % (right - left + 1) + left;

    int pivot = arr[k];  // �Ǻ��� ���� 
    int tmp1, tmp2;
    // �迭�� ù ��° ���ҿ� �Ǻ��� �ڸ��� ��ȯ�Ѵ�. 
    tmp1 = arr[left];
    arr[left] = arr[k];
    arr[k] = tmp1;

    int i = left + 1;
    int j = right;


    while (i < j)
    {
        while (i <= right && arr[i] <= pivot) { // pivot���� ���� ���� ã�� ������ i ���� 
            i++;
        }
        while (j > left && arr[j] >= pivot) // pivot���� ū ���� ã�� ������ j ���� 
        {
            j--;
        }
        if (i > j)          // i�� j�� �Ѿ ��� �Ǻ��� arr[j]�� ��ȯ 
        {
            tmp2 = arr[left];
            arr[left] = arr[j];
            arr[j] = tmp2;
        }
        else				// i�� j���� ���� ���  
        {
            tmp2 = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp2;
        }
    }

    // pivot�� �������� ���� �κй迭�� ������ �κй迭�� ���� ���ȣ�� 
    QuickSort(arr, left, j - 1);
    QuickSort(arr, j + 1, right);
    return 0;
}
