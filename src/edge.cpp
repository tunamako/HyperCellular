#include "include/edge.h"

#include <QPointF>

#include <math.h>
#include <algorithm>
#include <bits/stdc++.h> 
#include <cmath>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "include/math_helpers.h"


Edge::Edge() {}
QPointF Edge::reflectPoint(QPointF aPoint) {}
QVector<QPointF *> *Edge::reflectTile(QVector<QPointF *> *aPoint) {}
void Edge::draw(QPainter *painter) {}
void Edge::getRegion(QPointF *polygonCenter, QPointF origin, float radius) {}


LineEdge::LineEdge(QPointF pointA, QPointF pointB) {
    this->A = pointA;
    this->B = pointB;

    this->slope = slope_helper(A, B);

    if (std::isinf(this->slope)) {
        this->slope = std::numeric_limits<float>::infinity();
        this->y_intercept = std::numeric_limits<float>::infinity();
    } else {
        this->y_intercept = A.y() - (this->slope * A.x());
    }
}

QPointF LineEdge::reflectPoint(QPointF aPoint) {
    float denom = 1 + pow(A.x(), 2);
    float m = slope;
    float b = y_intercept;
    float x = aPoint.x();
    float y = aPoint.y();
    float invX;
    float invY;

    if (std::isinf(m)) {
        // axis of reflection is vertical
        invX = x - 2 * (x - A.x());
        invY = y;
    } else if (-0.001 <= m && m <= 0.001) {
        // axis of reflection is horizontal
        invX = x;
        invY = y - 2 * (y - A.y());
    } else {
        float intersectX = (x + m*(y-b))/(pow(m, 2) + 1);
        float intersectY = -1/m * intersectX + y + x/m;
        invX = x + 2 * (intersectX - x);
        invY = y + 2 * (intersectY - y);
    }
}

void LineEdge::draw(QPainter *painter) {
    painter->drawLine(A, B);
}

void LineEdge::getRegion(QPointF *polygonCenter, QPointF origin, float radius) {}


ArcEdge::ArcEdge(QPointF pointA, QPointF pointB, QPointF origin, float diskDiameter) {
    this->A = QPointF(pointA.x(), pointA.y());
    this->B = QPointF(pointB.x(), pointB.y());

    this->center = origin;
    this->radius = diskDiameter/2;
    QPointF pointC = this->reflectPoint(pointA);

    // Check if given points form a vertical segment: if so, rearrange points
    if (pointB.x() - pointA.x() <= 0.0001) {
        std::swap(pointB, pointC);
    } else if (pointC.x() - pointB.x() <= 0.0001) {
        std::swap(pointA, pointB);
    }

    float mA = slope_helper(pointA, pointB);
    float mB = slope_helper(pointB, pointC);
    if (std::isinf(mA) || std::isinf(mB)) {
        return;
    }

    // Use the intersection of the perpendicular bisectors of AB and BC as the center of the circle
    float centerX = (mA*mB*(pointA.y()-pointC.y()) + mB*(pointA.x()+pointB.x()) - mA*(pointB.x() + pointC.x())) / (2*(mB - mA));
    float centerY = (-1/mA)*(centerX - (pointA.x() + pointB.x())/2) + (pointA.y() + pointB.y())/2;
    if (std::isinf(centerY)) {
        centerY = (-1/mB)*(centerX - (pointB.x() + pointC.x())/2) + (pointB.y() + pointC.y())/2;
    }

    this->center = QPointF(centerX, centerY);
    this->radius = distance(this->center, pointA);
    this->collinear = false;
}

QPointF ArcEdge::reflectPoint(QPointF aPoint) {
    float x = aPoint.x();
    float y = aPoint.y();
    float x0 = center.x();
    float y0 = center.y();
    float invX = x0 + (pow(radius, 2) * (x-x0)) / (pow(x-x0, 2) + pow(y-y0, 2));
    float invY = y0 + (pow(radius, 2) * (y-y0)) / (pow(x-x0, 2) + pow(y-y0, 2));

    return QPointF(invX, invY);
}

void ArcEdge::draw(QPainter *painter) {
    // rectangle inscribed by aCircle
    QRectF rect(center.x() - radius, center.y() - radius, radius * 2, radius * 2);
    QLineF lineA(center, A);
    QLineF lineB(center, B);

    float sweepAngle = lineA.angleTo(lineB);
    if(sweepAngle > 180)
        sweepAngle -= 360;
    
    painter->drawArc(rect, 16 * lineA.angle(), 16 * sweepAngle);
}

void ArcEdge::getRegion(QPointF *polygonCenter, QPointF origin, float radius) {}

