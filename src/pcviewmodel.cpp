#include "include/pcviewmodel.h"

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVector>
#include <QBrush>
#include <QRegion>

#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

#include "include/math_helpers.h"

#define PI 3.14159265
#define PRECISION 10000

PoincareViewModel* PoincareViewModel::m_pInstance = NULL;

PoincareViewModel* PoincareViewModel::getInstance() {
    return m_pInstance;
}

PoincareViewModel* PoincareViewModel::getInstance(QWidget *parent) {
    if (!m_pInstance) {
        m_pInstance = new PoincareViewModel(parent);
    }
    return m_pInstance;
}

PoincareViewModel::PoincareViewModel(QWidget *parent) :
    QWidget(parent) {
    this->parent = parent;

    this->origin = QPointF();
    this->drawnCount = 0;
    this->sideCount = 5;
    this->adjacentCount = 4;
    this->renderDepth = 2;
    this->fillMode = false;
    this->tilesToUpdate = false;
    this->drawnTiles = std::map<float, std::unordered_set<float> >();
}

QVector<QPointF> PoincareViewModel::genCenterVertices() {
    QVector<QPointF> vertices = QVector<QPointF>();
    int p = sideCount;
    int q = adjacentCount;
    float dist = (diskDiameter/2) * sqrt(cos(M_PI/p + M_PI/q)*cos(M_PI/q) / (sin(2*M_PI/q) * sin(M_PI/p) + cos(M_PI/p + M_PI/q)* cos(M_PI/q)));
    float alpha = 2 * M_PI/p;

    float x, y;
    for (int i = 0; i < p; i++) {
        x = origin.x() + (dist) * cos(i * alpha);
        y = origin.y() + (dist) * sin(i * alpha);
        vertices.push_back(QPointF(x, y));
    }
    return vertices;
}

bool PoincareViewModel::tileExists(QPointF tileCenter) {
    float x = round(PRECISION * tileCenter.x())/PRECISION;
    float y = round(PRECISION * tileCenter.y())/PRECISION;

    if (x == y) {}
    return false;
    // drawnTiles[x][y] = tileCenter;
}

void PoincareViewModel::addTile(Tile *aTile) {
    float x = round(PRECISION * aTile->center.x())/PRECISION;
    float y = round(PRECISION * aTile->center.y())/PRECISION;
    if (x == y) {}
    // drawnTiles[x][y] = aTile;
}

void PoincareViewModel::drawTiling() {
    drawnCount = 0;
    drawnTiles.clear();
    tiles.clear();

    centerTile = new Tile(origin, genCenterVertices());
    centerTile->constructTiling(renderDepth);
    centerTile->draw();

    delete centerTile;
}

void PoincareViewModel::paintEvent(QPaintEvent *) {
    this->painter = new QPainter(this);
    this->painter->setRenderHint(QPainter::Antialiasing, true);

    diskDiameter = std::min(this->size().width(), this->size().height());
    origin.setX(this->size().width()/2);
    origin.setY(this->size().height()/2);
    this->painter->setPen(QPen(QColor(122, 0, 127, 255), 3));

    float radius = diskDiameter/2;
    float x = origin.x();
    float y = origin.y();

    QRect diskRect = QRect(x - radius, y - radius, diskDiameter, diskDiameter);
    diskRegion = QRegion(diskRect, QRegion::Ellipse);
    this->painter->setClipRegion(diskRegion);

    if (tilesToUpdate) {
        // TODO: Update tile colors
    } else {
        drawTiling();
    }

    this->painter->setClipping(false);
    this->painter->setPen(QPen(QColor(5, 0, 127, 255), 3));
    this->painter->drawEllipse(diskRect);
    this->painter->drawPoint(origin);

    this->painter->end();
    delete this->painter;
}

bool PoincareViewModel::areHyperbolicDims(int p, int q) {
    return ((p - 2) * (q - 2)) > 4;
}

int PoincareViewModel::setSideCount(int count) {
    if (areHyperbolicDims(count, adjacentCount)) {
        sideCount = count;
        update();
        return 0;
    } else {
        return -1;
    }
}

int PoincareViewModel::setAdjCount(int count) {
    if (areHyperbolicDims(sideCount, count)) {
        adjacentCount = count;
        update();
        return 0;
    } else {
        return -1;
    }
}

void PoincareViewModel::setRenderDepth(int depth) {
    renderDepth = depth;
    update();
}

void PoincareViewModel::updateTiles() {
    //tilesToUpdate = true;
    update();
}

void PoincareViewModel::toggleFillMode() {
}
