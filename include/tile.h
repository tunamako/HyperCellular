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
    explicit Tile(QPointF center, QVector<QPointF> vertices);
    ~Tile();

    int layer;
    QPointF center;
    std::vector<Edge *> edges;
    std::vector<Tile *> neighbors;
    QVector<QPointF> vertices;

    void constructTiling(int renderDepth);
    void draw();
    void update();

 private:
    void generateNeighbors();

    bool fillMode;
    PoincareViewModel *pcviewmodel;
    QColor color;
    QColor nextColor;
    QRegion region;
};

#endif // TILE_H
