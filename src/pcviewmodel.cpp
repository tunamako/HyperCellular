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
