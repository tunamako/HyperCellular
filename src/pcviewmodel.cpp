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

PoincareViewModel::PoincareViewModel(QWidget *parent) :
    QWidget(parent) {
    this->parent = parent;

    this->origin = new QPointF();

    this->drawnCount = 0;
    this->drawnTiles = std::map<float, std::unordered_set<float> >();
    this->sideCount = 5;
    this->adjacentCount = 4;
    this->renderDepth = 6;
    this->centerVertices = QVector<QPointF>();
}
PoincareViewModel::~PoincareViewModel() {}

void PoincareViewModel::genCenterVertices() {
    centerVertices.clear();
    int p = sideCount;
    int q = adjacentCount;
    float dist = (diskDiameter/2) * sqrt(cos(M_PI/p + M_PI/q)*cos(M_PI/q) / (sin(2*M_PI/q) * sin(M_PI/p) + cos(M_PI/p + M_PI/q)* cos(M_PI/q)));
    float alpha = 2 * M_PI/p;

    float x, y;
    for (int i = 0; i < p; i++) {
        x = origin->x() + (dist) * cos(i * alpha);
        y = origin->y() + (dist) * sin(i * alpha);
        centerVertices.push_back(QPointF(x, y));
    }
}

bool PoincareViewModel::hasBeenDrawn(QPointF *aPoint) {
    float precision = 1000;
    float x = round(precision * aPoint->x())/precision;
    float y = round(precision * aPoint->y())/precision;

    //drawnTiles[x][y] = aPoint;
}

void PoincareViewModel::addDrawnTile(Tile *aTile) {
    float precision = 1000;
    float x = round(precision * aTile->center->x())/precision;
    float y = round(precision * aTile->center->y())/precision;

    //drawnTiles[x][y] = aTile;
}

void PoincareViewModel::paintEvent(QPaintEvent *e) {
    this->painter = new QPainter(this);
    this->painter->setRenderHint(QPainter::Antialiasing, true);

    diskDiameter = std::min(this->size().width(), this->size().height());
    origin->setX(this->size().width()/2);
    origin->setY(this->size().height()/2);

    this->painter->setPen(QPen(QColor(122, 0, 127, 255), 3));

    float radius = diskDiameter/2;
    float x = origin->x();
    float y = origin->y();

    QRect diskRect = QRect(x - radius, y - radius, diskDiameter, diskDiameter);
    diskRegion = new QRegion(diskRect, QRegion::Ellipse);
    this->painter->setClipRegion(*diskRegion);

    if (tilesToUpdate) {
    } else {
        // drawTiling();
    }

    genCenterVertices();
    for (int i = 0; i < sideCount; i++) {
        this->painter->drawPoint(centerVertices[i]);
    }
    
    this->painter->setClipping(false);
    this->painter->setPen(QPen(QColor(5, 0, 127, 255), 3));
    this->painter->drawEllipse(diskRect);
    this->painter->drawPoint(*origin);

    this->painter->end();
    free(this->painter);
    free(this->diskRegion);
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
    tilesToUpdate = true;
    update();
}

void PoincareViewModel::toggleFillMode() {
}
