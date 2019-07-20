#include "pcviewmodel.h"
#include "edge.h"
#include "math_helpers.h"

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
	if (areHyperbolicDims(count, this->adjacentCount)) {
		this->sideCount = count;
		this->update();
		return 0;
	} else {
		return -1;
	}
}

int PoincareViewModel::setAdjCount(int count) {
	if (areHyperbolicDims(this->sideCount, count)) {
		this->adjacentCount = count;
		this->update();
		return 0;
	} else {
		return -1;
	}
}

void PoincareViewModel::setRenderDepth(int depth) {
	this->renderDepth = depth;
	this->update();
}

