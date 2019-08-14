#include "include/tile.h"

#include <QPointF>
#include <QVector>
#include <iostream>

#include <include/math_helpers.h>
#include <include/pcviewmodel.h>


Tile::Tile(QPointF center, QVector<QPointF> vertices) {
    this->pcviewmodel = PoincareViewModel::getInstance();
    this->center = center;
    this->edges = std::vector<Edge *>();
    this->neighbors = std::vector<Tile *>();
    this->vertices = vertices;

    this->color = QColor(0, 0, 0, 255);
    this->nextColor = nullptr;
    this->fillMode = pcviewmodel->fillMode;
    this->region = pcviewmodel->diskRegion;

    // TODO: Cleaner way to do this?
    for (int i = 0; i < vertices.size() - 1; ++i) {
        Edge * edge = Edge::create(vertices[i], vertices[i+1]);
        this->edges.push_back(edge);
    }
    Edge * edge = Edge::create(vertices.back(), vertices[0]);
    this->edges.push_back(edge);
}

Tile::~Tile() {
    for (auto edge : edges)
        delete edge;
    for (auto tile : neighbors)
        delete tile;
}

void Tile::generateNeighbors() {
    for (auto edge : this->edges) {
        Tile *reflectedTile = edge->reflectTile(this);

        if (reflectedTile != nullptr)
            this->neighbors.push_back(reflectedTile);
    }
}

void Tile::constructTiling(int layer) {
    this->layer = layer;
    this->generateNeighbors();
}

void Tile::draw() {
    QPainter *painter = pcviewmodel->painter;

    if (fillMode) {
        QPainterPath path = QPainterPath();
        path.addRegion(this->region);
        painter->fillPath(path, QBrush(this->color));
    }

    for (auto v : edges) {
        v->draw(painter);
    }
}

void Tile::update() {
    if (nextColor != nullptr) {
        this->color = this->nextColor;
        this->nextColor = nullptr;
    }
    this->draw();
}
