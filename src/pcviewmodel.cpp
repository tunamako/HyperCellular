#include "include/pcviewmodel.h"
#include "include/math_helpers.h"

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVector>
#include <QBrush>
#include <QRegion>
#include <QString>
#include <QOpenGLFunctions>

#include <math.h> 
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

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
PoincareViewModel::~PoincareViewModel(){}

void PoincareViewModel::paintEvent(QPaintEvent *e) {}

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
