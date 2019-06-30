#ifndef TILE_H
#define TILE_H

#include <vector>

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPointF>
#include <QRegion>
#include <QVector>
#include <QWidget>

#include "include/edge.h"
#include "include/pcviewmodel.h"

class PoincareViewModel;

class Tile {

public:
    explicit Tile(QVector<QPointF *> *vertices, PoincareViewModel *model,
                    int layer, QPointF *center);
    virtual ~Tile();

protected:
    void draw(QPainter *painter);
    void update(QPainter *painter);

private:
    bool fillMode;
    int layer;

    std::vector<Edge *> *edges;
    std::vector<Tile *> *neighbors;
    QVector<QPointF *> *vertices;
    QPointF *center;
    QColor *color;
    QColor *nextColor;
    QRegion *region;
};

#endif // TILE_H
