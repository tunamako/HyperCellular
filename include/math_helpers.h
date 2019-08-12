#ifndef HELP_H
#define HELP_H

#include <QPoint>

QPointF midpoint(QPointF A, QPointF B);
float distance(QPointF A, QPointF B);
float slope_helper(QPointF A, QPointF B);
bool areCollinear(QPointF A, QPointF B, QPointF C);
QPointF getCircleCenter(QPointF pt1, QPointF pt2, QPointF pt3);

#endif //HELP_H