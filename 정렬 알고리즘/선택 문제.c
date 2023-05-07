#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 8

int main()
{
    FILE* fp = NULL;
    fp = fopen("data.txt", "r");
    int result;			// k ��°�� ���� �� 
    int num;			// k ��° 
    if (fp == NULL)
    {
        printf("������ ���µ� �����߽��ϴ�. \n");
        return 1;
    }
    else
    {
        printf("������ ���µ� �����߽��ϴ�. \n");
    }
    int arr[MAX];
    int i = 0;
    // ���Ͽ��� �迭 �о����  
    while (fscanf(fp, "%d", &arr[i]) != EOF)
    {
        i++;
    }
    fclose(fp);
    printf("�� ��°�� ���� ���� ���Ͻʴϱ�? ");
    scanf("%d", &num);

    // ���� ���� �Լ� ���� 
    result = Selection(arr, 0, MAX - 1, num);

    // ��� ���� 
    fp = fopen("result.txt", "w");

    if (fp == NULL)
    {
        printf("������ ���µ� �����߽��ϴ�.\n");
        return 1;
    }

    fprintf(fp, "%d ", result);
    printf("%d����� ���� ���� %d�Դϴ�", num, result);
    fclose(fp);
    return 0;
}

int Selection(int arr[], int left, int right, int k)
{


    srand(time(NULL));
    // �Ǻ��� �����ϱ� ���� ���� �� p�� ���Ѵ�.
    int p = rand() % (right - left + 1) + left;

    int pivot = arr[p];     // �Ǻ��� ����

    int i = left + 1;       // pivot���� ���� ������ ���ʿ� �����ϱ� ���� �迭�� �ε��� 
    int j = right;          // pivot���� ū ������ �����ʾ� �����ϱ� ���� �迭�� �ε���

    int tmp1, tmp2;
    // �Ǻ��� ù ��° ������ �ڸ��� ��ȯ�Ѵ�. 
    tmp1 = arr[left];
    arr[left] = arr[p];
    arr[p] = tmp1;
    int S;
    while (i < j)
    {
        while (i <= right && arr[i] <= pivot) // pivot���� ���� ���� ã�� ������ i ����
        {
            i++;
        }
        while (j > left && arr[j] >= pivot)  // pivot���� ū ���� ã�� ������ j ����
        {
            j--;
        }
        if (i > j)    // i�� j�� �Ѿ ��� �Ǻ��� arr[j]�� ��ȯ 
        {
            tmp2 = arr[left];
            arr[left] = arr[j];
            arr[j] = tmp2;
        }
        else		  // i�� j���� ���� ���
        {
            tmp2 = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp2;
        }
    }

    // Small �׷��� ũ�� 
    S = (j - 1) - left + 1;
    // Small �׷쿡�� �ٽ� ã�´�. 
    if (k <= S) {
        Selection(arr, left, j - 1, k);
    }
    // k ����� ���� ���� ��ȯ 
    else if (k = S + 1) {
        return arr[j];
    }
    // large �׷쿡�� ã�´�. 
    else {
        Selection(arr, j + 1, right, k - S - 1);
    }
}