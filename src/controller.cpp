#include "include/controller.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>


CellularController::CellularController(QWidget *parent, PoincareViewModel *model) :
    QWidget(parent) {
    this->model = model;
    this->automaton = new WireWorld();

    resetTiles();
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
CellularController::~CellularController() {}


void CellularController::initAnimationButtons() {
    QHBoxLayout *hbox = new QHBoxLayout();

    QPushButton *startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()),
        this, SLOT(startAnimation()));

    QPushButton *stopButton = new QPushButton("Stop");
    connect(stopButton, SIGNAL(clicked()),
        this, SLOT(stopAnimation()));

    QPushButton *stepButton = new QPushButton("Step");
    connect(stepButton, SIGNAL(clicked()),
        this, SLOT(nextGeneration()));

    hbox->addWidget(startButton);
    hbox->addWidget(stopButton);
    hbox->addWidget(stepButton);

    this->vbox->addLayout(hbox);
}

void CellularController::initSpinBoxes() {
    // Initialize and connect spinboxes to their functions
    speedBox = new QSpinBox();
    speedBox->setRange(1, 100000);
    speedBox->setValue(animSpeed);
    connect(speedBox, SIGNAL(valueChanged(int)),
        this, SLOT(setSpeed(int)));

    sideCountBox = new QSpinBox();
    sideCountBox->setRange(3, 99);
    sideCountBox->setValue(model->sideCount);
    connect(sideCountBox, SIGNAL(valueChanged(int)),
        this, SLOT(setSideCount(int)));

    adjCountBox = new QSpinBox();
    adjCountBox->setRange(3, 99);
    adjCountBox->setValue(model->adjacentCount);
    connect(adjCountBox, SIGNAL(valueChanged(int)),
        this, SLOT(setAdjCount(int)));

    renderDepthBox = new QSpinBox();
    renderDepthBox->setRange(1, 99);
    renderDepthBox->setValue(model->renderDepth);
    connect(renderDepthBox, SIGNAL(valueChanged(int)),
        this, SLOT(setRenderDepth(int)));

    // Add Labels for each spinbox and use hboxes to collect them
    QHBoxLayout *speedLayout = new QHBoxLayout();
    speedLayout->addWidget(new QLabel("Speed (ms)"));
    speedLayout->addWidget(speedBox);

    QHBoxLayout *sideCountLayout = new QHBoxLayout();
    sideCountLayout->addWidget(new QLabel("Side Count"));
    sideCountLayout->addWidget(sideCountBox);

    QHBoxLayout *adjCountLayout = new QHBoxLayout();
    adjCountLayout->addWidget(new QLabel("Adjacency Count"));
    adjCountLayout->addWidget(adjCountBox);

    QHBoxLayout *renderDepthLayout = new QHBoxLayout();
    renderDepthLayout->addWidget(new QLabel("Render Depth"));
    renderDepthLayout->addWidget(renderDepthBox);

    // Add label/spinbox hboxes to main vbox layout
    this->vbox->addLayout(speedLayout);
    this->vbox->addLayout(sideCountLayout);
    this->vbox->addLayout(adjCountLayout);
    this->vbox->addLayout(renderDepthLayout);
}

void CellularController::initControlButtons() {
    QPushButton *clearButton = new QPushButton("Clear");
    connect(clearButton, SIGNAL(clicked()),
        this, SLOT(resetTiles()));

    QPushButton *randomizeButton = new QPushButton("Randomize");
    connect(randomizeButton, SIGNAL(clicked()),
        this, SLOT(randomize()));

    QPushButton *toggleFillButton = new QPushButton("Toggle Fill");
    connect(toggleFillButton, SIGNAL(clicked()),
        this, SLOT(toggleFill()));

    this->vbox->addWidget(clearButton);
    this->vbox->addWidget(randomizeButton);
    this->vbox->addWidget(toggleFillButton);
}

void CellularController::startAnimation() {
    timer->start(animSpeed);
}

void CellularController::stopAnimation() {
    timer->stop();
}

void CellularController::nextGeneration() {
}

void CellularController::setSpeed(int speed) {
    animSpeed = speed;
    timer->setInterval(speed);
}

void CellularController::setSideCount(int count) {
    int current = model->sideCount;

    // If the input is invalid, set the spinbox value to what it was previously
    if (model->setSideCount(count) != 0) {
        sideCountBox->setValue(current);
    }
}

void CellularController::setAdjCount(int count) {
    int current = model->adjacentCount;

    // If the input is invalid, set the spinbox value to what it was previously
    if (model->setAdjCount(count) != 0) {
        adjCountBox->setValue(current);
    }
}

void CellularController::setRenderDepth(int depth) {
    model->setRenderDepth(depth);
}

void CellularController::resetTiles() {
    automaton->fill(&model->tiles);
    model->updateTiles();
}
void CellularController::randomize() {
    automaton->randomize(&model->tiles);
    model->updateTiles();
}
void CellularController::toggleFill() {
    model->toggleFillMode();
}

//void CellularController::clicked(QMouseEvent *e) {}
