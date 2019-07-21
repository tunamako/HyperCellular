#include "include/tile.h"

#include <QPointF>
#include <QVector>


Tile::Tile(QVector<QPointF> vertices, PoincareViewModel &model,
    int layer, QPointF center) {

    this->edges = std::vector<Edge *>();
    this->neighbors = std::vector<Tile *>();
    this->center = center;
    this->layer = layer;
    this->vertices = vertices;
    this->color = QColor(0, 0, 0, 255);
    this->nextColor = nullptr;
    this->fillMode = model.fillMode;
    this->region = model.diskRegion;
}

void Tile::draw(QPainter *painter) {
    if (fillMode) {
        QPainterPath path = QPainterPath();
        path.addRegion(this->region);
        painter->fillPath(path, QBrush(this->color));
    }

    for (int i = 0; i < this->vertices.size(); i++) {
        painter->drawPoint(this->vertices[i]);
    }
}

void Tile::update(QPainter *painter) {
    if (nextColor != nullptr) {
        this->color = this->nextColor;
        this->nextColor = nullptr;
    }
    this->draw(painter);
}
