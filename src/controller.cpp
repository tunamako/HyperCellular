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
    //this->automaton = new WireWorld();

    //this->resetTiles();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextGeneration()));
    animSpeed = 100;

    vbox = new QVBoxLayout();
    initAnimationButtons();
    initSpinBoxes();
    initControlButtons();

    vbox->addStretch(1);
    this->setLayout(vbox);
}
CellularController::~CellularController(){}


void CellularController::initAnimationButtons() {
	QHBoxLayout *hbox = new QHBoxLayout();

	QPushButton *startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startAnimation()));

	QPushButton *stopButton = new QPushButton("Stop");
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));

	QPushButton *stepButton = new QPushButton("Step");
    connect(stepButton, SIGNAL(clicked()), this, SLOT(nextGeneration()));

	hbox->addWidget(startButton);
	hbox->addWidget(stopButton);
	hbox->addWidget(stepButton);

	this->vbox->addLayout(hbox);

}

void CellularController::initSpinBoxes() {

}

void CellularController::initControlButtons() {

}

void CellularController::startAnimation() {
	timer->start(animSpeed);
}
void CellularController::stopAnimation() {
	timer->stop();
}
void CellularController::nextGeneration() {
	std::cout << "wah" << std::endl;
}
void CellularController::setSpeed(int speed) {}
void CellularController::setSideCount(int count) {}
void CellularController::setAdjCount(int count) {}
void CellularController::setRenderDepth(int depth) {}
void CellularController::resetTiles() {}
void CellularController::randomize() {}
void CellularController::toggleFill() {}
