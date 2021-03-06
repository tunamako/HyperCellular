#ifndef CELLULARCONTROLLER_H
#define CELLULARCONTROLLER_H

#include <QMouseEvent>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "include/pcviewmodel.h"
#include "include/automaton.h"

namespace Ui {
class CellularController;
}

class CellularController : public QWidget {
    Q_OBJECT

 public:
    explicit CellularController(QWidget *parent);
    ~CellularController();

    void clicked(QMouseEvent *e);

 public slots:
    void startAnimation();
    void stopAnimation();
    void nextGeneration();

    void setSpeed(int speed);
    void setSideCount(int count);
    void setAdjCount(int count);
    void setRenderDepth(int depth);

    void resetTiles();
    void randomize();
    void toggleFill();

 private:
    PoincareViewModel *model;
    Automaton *automaton;
    int animSpeed;
    QTimer *timer;
    QVBoxLayout *vbox;
    QSpinBox *speedBox;
    QSpinBox *sideCountBox;
    QSpinBox *adjCountBox;
    QSpinBox *renderDepthBox;

    void initAnimationButtons();
    void initSpinBoxes();
    void initControlButtons();
};

#endif // CELLULARCONTROLLER_H
