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

PoincareViewModel::PoincareViewModel(QWidget *parent) :
    QWidget(parent) {
    this->parent = parent;

    this->centerVertices = new QVector<QPointF *>();
    this->origin = new QPointF();

    this->drawnCount = 0;
    this->drawnTiles = std::map<float, std::unordered_set<float> >();
    this->sideCount = 5;
    this->adjacentCount = 4;
    this->renderDepth = 6;
}
PoincareViewModel::~PoincareViewModel() {}

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

    QRect *diskRect = new QRect(x - radius, y - radius, diskDiameter, diskDiameter);
    diskRegion = new QRegion(*diskRect, QRegion::Ellipse);
    this->painter->setClipRegion(*diskRegion);

    if (tilesToUpdate) {
    } else {
        // drawTiling();
    }

    this->painter->setClipping(false);
    this->painter->setPen(QPen(QColor(5, 0, 127, 255), 3));
    this->painter->drawEllipse(*diskRect);
    this->painter->drawPoint(*origin);

    this->painter->end();
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
