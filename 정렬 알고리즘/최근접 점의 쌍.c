#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// x좌표 y좌표를 받을 구조체 선언
typedef struct Point {
    double x, y;
}Points;

int CompareX(const void* a, const void* b); // x좌표를 기준삼아 오름차순으로 정렬해주는 함수
double Distance(Points p1, Points p2);	    // 점 p1과 점 p2의 거리를 구하는 함수
double ClosestPair(Points* points, int n);	    // 최근접 점의 쌍의 거리를 반환하는 함수
void testClosetPair_File();		    // 파일로 점의 집합을 구조체 배열로 받아들이고 ClosestPair를 실행

int main(void) {
    testClosetPair_File();	// 파일을 읽어 ClosestPair함수 실행
    return 0;
}

int CompareX(const void* a, const void* b) { // x 좌표를 기준으로 오름차순 정렬
    Points* p1 = (Points*)a;
    Points* p2 = (Points*)b;
    return (p1->x - p2->x);
}
// math.h 라이브러리 함수를 사용해 두 점의 거리를 구한다.
double Distance(Points p1, Points p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); }

double ClosestPair(Points* points, int n) {
    int i, j, k;
    // n이 3 이하일 때 n개의 점 중 최단거리를 찾는다.
    if (n <= 3) { // 기저 사례 
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
    // x 좌표를 기준으로 정렬된 배열을 두 개로 분할
    int mid = n / 2;
    double mid_x = points[mid].x;
    double dl = ClosestPair(points, mid);
    double dr = ClosestPair(points + mid, n - mid);

    // dl과 dr중 작은 값을 d에 저장
    double d = fmin(dl, dr);

    // 중앙 영역에서 최단 거리를 갱신할 수 있는 후보점들을 찾는 과정
    Points strip[100];
    j = 0;
    for (i = 0; i < n; i++) {
        // 점들의 x좌표가 중앙 영역에 해당하는지 검사하는 반복문
        if (fabs(points[i].x - mid_x) < d) {
            strip[j] = points[i];
            j++;
        }
    }
    // 중앙 영역에서 최단 거리 갱신 
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
    // 구조체 배열 선언
    Points points[100];
    FILE* fp = NULL;
    // 파일 읽기
    fp = fopen("CPdata.txt", "r");
    if (fp == NULL) {
        printf("CPdata 파일을 여는데 실패했습니다. \n");
        return 0;
    }
    else {
        printf("CPdata 파일을 여는데 성공했습니다. \n");
    }
    // 파일의 끝을 만날때까지 두 실수를 points[i].x와 points[i].y에 저장
    while (fscanf(fp, "%lf %lf\n", &points[i].x, &points[i].y) != EOF) {
        printf("x = %.2lf, y = %.2lf\n", points[i].x, points[i].y);
        i++;
    }
    fclose(fp);
    // x좌표를 기준삼아 오름차순으로 정렬
    qsort(points, 4, sizeof(Points), CompareX);
    // 최근접 점 쌍의 거리
    double min_dist = ClosestPair(points, 4);

    printf("최근접 점 쌍의 거리는 %.2lf\n", min_dist);
}