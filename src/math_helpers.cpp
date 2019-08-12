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

QPointF getCircleCenter(QPointF pt1, QPointF pt2, QPointF pt3) {
    double yDelta_a= pt2.y() - pt1.y();
    double xDelta_a= pt2.x() - pt1.x();
    double yDelta_b= pt3.y() - pt2.y();
    double xDelta_b= pt3.x() - pt2.x();
    double centerX;
    double centerY;


    if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
        centerX = 0.5*(pt2.x() + pt3.x());
        centerY = 0.5*(pt1.y() + pt2.y());
        return QPointF(centerX, centerY);
    } else {
        double aSlope = yDelta_a / xDelta_a;
        double bSlope = yDelta_b / xDelta_b;

        // calc center
        centerX = (aSlope*bSlope*(pt1.y() - pt3.y()) + bSlope*(pt1.x() + pt2 .x()) - aSlope*(pt2.x()+pt3.x()) )/(2* (bSlope-aSlope) );
        centerY = -1*(centerX - (pt1.x()+pt2.x())/2)/aSlope +  (pt1.y()+pt2.y())/2;
    }
    return QPointF(centerX, centerY);
}