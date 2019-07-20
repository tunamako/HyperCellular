#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>

#include "include/pcviewmodel.h"
#include "include/controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private:
    PoincareViewModel *model;
    CellularController *controller;

    QHBoxLayout *hbox;
};

#endif // MAINWINDOW_H
