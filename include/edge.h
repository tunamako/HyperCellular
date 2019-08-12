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

    static Edge *create(QPointF pointA, QPointF pointB, QPointF origin, float diskDiameter);

    QVector<QPointF> reflectTile(QVector<QPointF> aPoint);

    virtual QPointF reflectPoint(QPointF) = 0;
    virtual void draw(QPainter *);
    virtual void getRegion(QPointF *, QPointF, float);
};

class LineEdge : public Edge {
 public:
    LineEdge(QPointF pointA, QPointF pointB);

    virtual QPointF reflectPoint(QPointF aPoint);
    virtual void draw(QPainter *painter);
    virtual void getRegion(QPointF *polygonCenter, QPointF origin, float radius);

 private:
    QPointF A;
    QPointF B;
    float y_intercept;
    float slope;
};

class ArcEdge : public Edge {
 public:
    ArcEdge(QPointF pointA, QPointF pointB, QPointF origin, float diskDiameter);

    virtual QPointF reflectPoint(QPointF aPoint);
    virtual void draw(QPainter *painter);
    virtual void getRegion(QPointF *polygonCenter, QPointF origin, float radius);

 private:
    QPointF A;
    QPointF B;
    QPointF center;
    float radius;
    bool collinear;
};

#endif // EDGE_H