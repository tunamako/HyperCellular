#ifndef TILE_H
#define TILE_H

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPointF>
#include <QRegion>
#include <QVector>
#include <QWidget>

#include <vector>

#include "include/edge.h"
#include "include/pcviewmodel.h"

class Edge;
class PoincareViewModel;

class Tile {
 public:
    explicit Tile(QVector<QPointF> &vertices, PoincareViewModel &model,
                    int layer, QPointF center);
    ~Tile();
    int layer;
    QPointF center;
    std::vector<Edge *> edges;
    std::vector<Tile *> neighbors;
    QVector<QPointF> vertices;

    void draw(QPainter *painter);
    void update(QPainter *painter);

 private:
    bool fillMode;

    QColor color;
    QColor nextColor;
    QRegion region;
};

#endif // TILE_H
