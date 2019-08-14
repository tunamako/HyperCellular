#include "include/mainwindow.h"

#include <QMainWindow>
#include <QHBoxLayout>

#include "include/pcviewmodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
        this->model = PoincareViewModel::getInstance(this);
        this->controller = new CellularController(this);

        this->hbox = new QHBoxLayout();
        this->hbox->addWidget(this->controller);
        this->hbox->addWidget(this->model);

        this->hbox->setContentsMargins(0, 0, 0, 0);
        this->hbox->setStretch(0, 1);
        this->hbox->setStretch(1, 4);

        QWidget *widget = new QWidget();
        widget->setLayout(this->hbox);
        this->setCentralWidget(widget);

        this->setWindowTitle("HyperCellular");
        this->setBaseSize(500, 500);
        this->show();
}

MainWindow::~MainWindow() {
}
