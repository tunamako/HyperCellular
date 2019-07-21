#include "include/math_helpers.h"

#include <QLineF>
#include <QPoint>

#include <math.h>
#include <algorithm>
#include <iostream>

float distance(QPointF *A, QPointF *B) {
    return sqrt(pow((B->x() - A->x()), 2) + pow((B->y() - A->y()), 2));
}

QPointF midpoint(QPointF *A, QPointF *B) {
    return QPointF((A->x() + B->x())/2, (A->y() + B->y())/2);
}

float slope(QPointF *A, QPointF *B) {
    float diffY = B->y() - A->y();
    float diffX = B->x() - A->x();

    if (diffX != 0) {
        return diffY / diffX;
    } else {
        return NULL;
    }
}

bool areCollinear(QPointF *A, QPointF *B, QPointF *C) {
    float slopeBC = slope(B, C);
    float slopeAB = slope(A, B);

    if (slopeBC != NULL && slopeAB != NULL) {
        return abs(slopeBC - slopeAB) <= 0.0000001;
    } else {
        return false;
    }
}
