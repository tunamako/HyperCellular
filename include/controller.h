#ifndef CELLULARCONTROLLER_H
#define CELLULARCONTROLLER_H

#include "pcviewmodel.h"

#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>


namespace Ui {
class CellularController;
}

class CellularController : public QWidget {

public:
    explicit CellularController(QWidget *parent, PoincareViewModel *model);
    ~CellularController();

    void nextGeneration();
    void setSpeed(int speed);
    void setSideCount(int count);
    void setAdjCount(int count);
    void setRenderDepth(int depth);
    void resetTiles();
    void randomize();
    void toggleFill();
    //void clicked();


private:

	PoincareViewModel *model;
	//Automaton *automaton;
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
