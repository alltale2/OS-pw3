#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct {
    int x;
    int y;
    int weight;
} Point;

Point** generatePoints(int weightFrom, int weightTo, int xFrom, int xTo, int yFrom, int yTo, int length);
void printPoints(Point** points, int length);
int randomIntNumberInRange(int from, int to);
int indexPointLowestWeight(Point** points, int length);
int findClosestPointIndex(Point** points, int length, int indexPointFrom);
Point** removePointWithLowestWeightAndSetWeightOfNearestPoint(Point** points, int length);

int main() {

    srand(time(NULL));

    int length = 5;
    Point** points = generatePoints(2, 20, 2, 20, 2, 20, length);
    printPoints(points, length);
    printf("\n");

    while (length > 1) {
        points = removePointWithLowestWeightAndSetWeightOfNearestPoint(points, length);
        length--;

        printPoints(points, length);
        printf("\n");
    }

    printf("LAST POINT INFO\nx: %d, y: %d, weight: %d\n", points[0]->x, points[0]->y, points[0]->weight);

    return 0;
}


Point** generatePoints(int weightFrom, int weightTo, int xFrom, int xTo, int yFrom, int yTo, int length){
    Point** points = (Point**) malloc(sizeof(Point*) * length);

    int index;
    for (index = 0; index < length; index++){
        Point* point = (Point*) malloc(sizeof(Point));
        point->x = randomIntNumberInRange(xFrom, xTo);
        point->y = randomIntNumberInRange(yFrom, yTo);
        point->weight = randomIntNumberInRange(weightFrom, weightTo);
        points[index] = point;
    }

    return points;
}

void printPoints(Point** points, int length) {
    int index;
    Point* point;
    for (index = 0; index < length; index++) {
        point = points[index];
        printf("x: %d, y: %d, weight: %d\n", point->x, point->y, point->weight);
    }
}

int randomIntNumberInRange(int from, int to) {
    return rand() % (to - from) + from;
}

Point** removePointWithLowestWeightAndSetWeightOfNearestPoint(Point** points, int length) {
    int indexLowerWeightPoint = indexPointLowestWeight(points, length);
    int closestPointIndex = findClosestPointIndex(points, length, indexLowerWeightPoint);

    Point* lowerWeightPoint = points[indexLowerWeightPoint];
    Point* closestPoint = points[closestPointIndex];

    closestPoint->weight += lowerWeightPoint->weight;

    free(points[indexLowerWeightPoint]);

    int index;
    for (index = indexLowerWeightPoint; index < length - 1; index++){
        points[index] = points[index + 1];
    }

    points = realloc(points, length);

    return points;
}

int indexPointLowestWeight(Point** points, int length) {
    int lowestWeightPointIndex = 0;
    int index;
    for (index = 0; index < length; index++){
        if (points[lowestWeightPointIndex]->weight > points[index]->weight){
            lowestWeightPointIndex = index;
        }
    }
    return lowestWeightPointIndex;
}

int findClosestPointIndex(Point** points, int length, int indexPointFrom) {
    Point* pointFrom = points[indexPointFrom];
    int closesPointIndex = 0;
    int minDistance = __INT_MAX__;

    int index;
    for (index = 0; index < length; index++){
        if (index == indexPointFrom){
            continue;
        }

        Point* pointTo = points[index];
        int distance = sqrt(pow(pointTo->x - pointFrom->x, 2) + pow(pointTo->y - pointFrom->y, 2));

        if (minDistance > distance) {
            minDistance = distance;
            closesPointIndex = index;
        }
    }

    return closesPointIndex;
}
