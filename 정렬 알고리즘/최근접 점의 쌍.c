#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// x��ǥ y��ǥ�� ���� ����ü ����
typedef struct Point {
    double x, y;
}Points;

int CompareX(const void* a, const void* b); // x��ǥ�� ���ػ�� ������������ �������ִ� �Լ�
double Distance(Points p1, Points p2);	    // �� p1�� �� p2�� �Ÿ��� ���ϴ� �Լ�
double ClosestPair(Points* points, int n);	    // �ֱ��� ���� ���� �Ÿ��� ��ȯ�ϴ� �Լ�
void testClosetPair_File();		    // ���Ϸ� ���� ������ ����ü �迭�� �޾Ƶ��̰� ClosestPair�� ����

int main(void) {
    testClosetPair_File();	// ������ �о� ClosestPair�Լ� ����
    return 0;
}

int CompareX(const void* a, const void* b) { // x ��ǥ�� �������� �������� ����
    Points* p1 = (Points*)a;
    Points* p2 = (Points*)b;
    return (p1->x - p2->x);
}
// math.h ���̺귯�� �Լ��� ����� �� ���� �Ÿ��� ���Ѵ�.
double Distance(Points p1, Points p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); }

double ClosestPair(Points* points, int n) {
    int i, j, k;
    // n�� 3 ������ �� n���� �� �� �ִܰŸ��� ã�´�.
    if (n <= 3) { // ���� ��� 
        double min_dist = 99999.0;
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                double dist = Distance(points[i], points[j]);
                if (dist < min_dist)
                    min_dist = dist;
            }
        }
        return min_dist;
    }
    // x ��ǥ�� �������� ���ĵ� �迭�� �� ���� ����
    int mid = n / 2;
    double mid_x = points[mid].x;
    double dl = ClosestPair(points, mid);
    double dr = ClosestPair(points + mid, n - mid);

    // dl�� dr�� ���� ���� d�� ����
    double d = fmin(dl, dr);

    // �߾� �������� �ִ� �Ÿ��� ������ �� �ִ� �ĺ������� ã�� ����
    Points strip[100];
    j = 0;
    for (i = 0; i < n; i++) {
        // ������ x��ǥ�� �߾� ������ �ش��ϴ��� �˻��ϴ� �ݺ���
        if (fabs(points[i].x - mid_x) < d) {
            strip[j] = points[i];
            j++;
        }
    }
    // �߾� �������� �ִ� �Ÿ� ���� 
    for (i = 0; i < j - 1; i++) {
        for (k = i + 1; k < j && (strip[k].y - strip[i].y) < d; k++) {
            double dist = Distance(strip[i], strip[k]);
            if (dist < d)
                d = dist;
        }
    }
    return d;
}

int testClosetPair_File() {
    int i = 0;
    // ����ü �迭 ����
    Points points[100];
    FILE* fp = NULL;
    // ���� �б�
    fp = fopen("CPdata.txt", "r");
    if (fp == NULL) {
        printf("CPdata ������ ���µ� �����߽��ϴ�. \n");
        return 0;
    }
    else {
        printf("CPdata ������ ���µ� �����߽��ϴ�. \n");
    }
    // ������ ���� ���������� �� �Ǽ��� points[i].x�� points[i].y�� ����
    while (fscanf(fp, "%lf %lf\n", &points[i].x, &points[i].y) != EOF) {
        printf("x = %.2lf, y = %.2lf\n", points[i].x, points[i].y);
        i++;
    }
    fclose(fp);
    // x��ǥ�� ���ػ�� ������������ ����
    qsort(points, 4, sizeof(Points), CompareX);
    // �ֱ��� �� ���� �Ÿ�
    double min_dist = ClosestPair(points, 4);

    printf("�ֱ��� �� ���� �Ÿ��� %.2lf\n", min_dist);
}