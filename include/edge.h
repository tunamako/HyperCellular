#ifndef EDGE_H
#define EDGE_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QVector>

class Edge {

public:
    Edge();
    virtual ~Edge();

    virtual QPointF *reflectPoint(QPointF *aPoint);
    QVector<QPointF *> *reflectPoints(QVector<QPointF *> *aPoint);
    virtual void draw(QPainter *painter);
};

class LineEdge : public Edge {

public:
    LineEdge(QPointF *A, QPointF *B);
    virtual ~LineEdge();

    virtual QPointF *reflectPoint(QPointF *aPoint);
    virtual void draw(QPainter *painter);


protected:
    QPointF *A;
    QPointF *B;
    float y_intercept;
    float slope;
};

class ArcEdge : public Edge {

public:
    ArcEdge(QPointF *A, QPointF *B, QPointF *origin, int diskDiameter);
    virtual ~ArcEdge();

    virtual QPointF *reflectPoint(QPointF *aPoint);
    virtual void draw(QPainter *painter);

protected:
    QPointF *A;
    QPointF *B;
    QPointF *center;
    float radius;
};

#endif // EDGE_H