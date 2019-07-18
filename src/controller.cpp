#include "controller.h"

#include <math.h> 
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

CellularController::CellularController(QWidget *parent, PoincareViewModel *model) :
    QWidget(parent) {

    this->model = model;

}
CellularController::~CellularController(){}


void CellularController::initAnimationButtons() {

}

void CellularController::initSpinBoxes() {

}

void CellularController::initControlButtons() {

}

void CellularController::nextGeneration() {}
void CellularController::setSpeed(int speed) {}
void CellularController::setSideCount(int count) {}
void CellularController::setAdjCount(int count) {}
void CellularController::setRenderDepth(int depth) {}
void CellularController::resetTiles() {}
void CellularController::randomize() {}
void CellularController::toggleFill() {}
