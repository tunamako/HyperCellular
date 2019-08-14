#include "include/edge.h"

#include <QPointF>
#include <QtDebug>

#include <math.h>
#include <algorithm>
#include <bits/stdc++.h> 
#include <cmath>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "include/math_helpers.h"
#include "include/pcviewmodel.h"
#include "include/tile.h"

bool arePerpendicular(QPointF pt1, QPointF pt2, QPointF pt3) {
    // Check the given points are perpendicular to x or y axis 
    double yDelta_a = fabs(pt2.y() - pt1.y());
    double xDelta_a = fabs(pt2.x() - pt1.x());
    double yDelta_b = fabs(pt3.y() - pt2.y());
    double xDelta_b = fabs(pt3.x() - pt2.x());

    if (xDelta_a <= 0.000000001 && yDelta_b <= 0.000000001) {
        return false;
    }

    return (yDelta_a <= 0.000000001 || \
            yDelta_b <= 0.000000001 || \
            xDelta_a <= 0.000000001 || \
            xDelta_b <= 0.000000001);
}

Edge::Edge() {}
Edge::~Edge() {}

Edge *Edge::create(QPointF pointA, QPointF pointB) {
    QPointF origin = PoincareViewModel::getInstance()->origin;
    float diskDiameter = PoincareViewModel::getInstance()->diskDiameter;

    if (areCollinear(pointA, pointB, origin)) {
        return new LineEdge(pointA, pointB);
    } else{
        return new ArcEdge(pointA, pointB, origin, diskDiameter);
    }
}

QVector<QPointF> Edge::reflectTile(Tile *aTile) {
    QVector<QPointF> ret;
    for (auto v : aTile->vertices) {
        ret.push_back(this->reflectPoint(v));
    }
    return ret;
}

void Edge::draw(QPainter *) {}
void Edge::getRegion(QPointF *, QPointF, float) {}


LineEdge::LineEdge(QPointF pointA, QPointF pointB) {
    this->A = pointA;
    this->B = pointB;

    this->slope = slope_helper(A, B);

    if (std::isinf(this->slope) || std::isnan(std::abs(this->slope))) {
        this->slope = std::numeric_limits<float>::infinity();
        this->y_intercept = std::numeric_limits<float>::infinity();
    } else {
        this->y_intercept = A.y() - (this->slope * A.x());
    }
}

QPointF LineEdge::reflectPoint(QPointF aPoint) {
    float m = slope;
    float b = y_intercept;
    float x = aPoint.x();
    float y = aPoint.y();
    float invX;
    float invY;

    if (std::isinf(m) || std::isnan(std::abs(m))) {
        // axis of reflection is vertical
        invX = x - 2 * (x - A.x());
        invY = y;
    } else if (fabs(m) < 0.000000001) {
        // axis of reflection is horizontal
        invX = x;
        invY = y - 2 * (y - A.y());
    } else {
        float intersectX = (x + m*(y-b))/(pow(m, 2) + 1);
        float intersectY = -1/m * intersectX + y + x/m;
        invX = x + 2 * (intersectX - x);
        invY = y + 2 * (intersectY - y);
    }
    return QPointF(invX, invY);
}

void LineEdge::draw(QPainter *painter) {
    painter->drawLine(A, B);
}

void LineEdge::getRegion(QPointF *polygonCenter, QPointF origin, float radius) {}



ArcEdge::ArcEdge(QPointF pA, QPointF pB, QPointF origin, float diskDiameter) {
    this->A = QPointF(pA.x(), pA.y());
    this->B = QPointF(pB.x(), pB.y());
    this->center = origin;
    this->radius = diskDiameter/2;
    QPointF pC = this->reflectPoint(pA);

    if (!arePerpendicular(pA, pB, pC)) {
        this->center = getCircleCenter(pA, pB, pC);
    } else if (!arePerpendicular(pA, pC, pB)) {
        this->center = getCircleCenter(pA, pC, pB);
    } else if (!arePerpendicular(pB, pA, pC)) {
        this->center = getCircleCenter(pB, pA, pC);
    } else if (!arePerpendicular(pB, pC, pA)) {
        this->center = getCircleCenter(pB, pC, pA);
    } else if (!arePerpendicular(pC, pB, pA)) {
        this->center = getCircleCenter(pC, pB, pA);
    } else if (!arePerpendicular(pA, pC, pB)) {
        this->center = getCircleCenter(pC, pA, pB);
    }

    this->radius = distance(this->center, pA);
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

