#include "include/math_helpers.h"

#include <QLineF>
#include <QPoint>

#include <math.h>
#include <cmath>
#include <algorithm>
#include <iostream>

float distance(QPointF A, QPointF B) {
    return sqrt(pow((B.x() - A.x()), 2) + pow((B.y() - A.y()), 2));
}

QPointF midpoint(QPointF A, QPointF B) {
    return QPointF((A.x() + B.x())/2, (A.y() + B.y())/2);
}

float slope_helper(QPointF A, QPointF B) {
    float diffY = B.y() - A.y();
    float diffX = B.x() - A.x();

    return diffY / diffX;
}

bool areCollinear(QPointF A, QPointF B, QPointF C) {
    float slopeBC = slope_helper(B, C);
    float slopeAB = slope_helper(A, B);

    if (std::isinf(slopeBC) || std::isinf(slopeAB)
        || std::isnan(std::abs(slopeBC))
        || std::isnan(std::abs(slopeAB))) {
        return false;
    } else {
        return abs(slopeBC - slopeAB) <= 0.0000001;
    }
}
