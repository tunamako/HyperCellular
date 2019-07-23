#include "include/tile.h"

#include <QPointF>
#include <QVector>

#include <include/math_helpers.h>

Tile::Tile(QVector<QPointF> &vertices, PoincareViewModel &model,
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

    for (int i = 0; i < vertices.size() - 1; i++) {
        if (areCollinear(vertices[i], vertices[i+1], model.origin)) {
            LineEdge *edge = new LineEdge(vertices[i], vertices[i+1]);
            this->edges.push_back(edge);
        } else{
            ArcEdge *edge = new ArcEdge(vertices[i], vertices[i+1], model.origin, model.diskDiameter);
            this->edges.push_back(edge);
        }
    }
    if (areCollinear(vertices[vertices.size()-1], vertices[0], model.origin)) {
        LineEdge *edge = new LineEdge(vertices[vertices.size()-1], vertices[0]);
        this->edges.push_back(edge);
    } else{
        ArcEdge *edge = new ArcEdge(vertices[vertices.size()-1], vertices[0], model.origin, model.diskDiameter);
        this->edges.push_back(edge);
    }
}

void Tile::draw(QPainter *painter) {
    if (fillMode) {
        QPainterPath path = QPainterPath();
        path.addRegion(this->region);
        painter->fillPath(path, QBrush(this->color));
    }

    for (auto v : edges) {
        v->draw(painter);
    }
}

void Tile::update(QPainter *painter) {
    if (nextColor != nullptr) {
        this->color = this->nextColor;
        this->nextColor = nullptr;
    }
    this->draw(painter);
}
