#ifndef POINCAREVIEW_H
#define POINCAREVIEW_H

#include <string>
#include <map>
#include <unordered_set>

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPointF>
#include <QRegion>
#include <QVector>
#include <QWidget>

#include "include/tile.h"


namespace Ui {
class PoincareViewModel;
}

class PoincareViewModel : public QWidget {

public:
    explicit PoincareViewModel(QWidget *parent);
    virtual ~PoincareViewModel();

protected:
    bool areHyperbolicDims(int p, int q);
    int setAdjCount(int count);
    int setSideCount(int count);
    void setRenderDepth(int depth);
    void toggleFillMode();
    void updateTiles();
    // void mousePressEvent();

private:
    bool fillMode;
    bool tilesToUpdate;
    int adjacentCount;
    int diskDiameter;
    int drawnCount;
    int sideCount;
    int renderDepth;

    QWidget *parent;
    QVector<QPointF *> *centerVertices;
    QPainterPath *diskPath;
    QRegion *diskRegion;
    QPainter *painter;
    QPointF *origin;

    std::map<float, std::unordered_set<float> > drawnTiles;
    QVector<Tile *> *tiles;

    void drawTiling();    
    QVector<QPointF *> getCenterVertices();
    Tile *hasBeenDrawn(QPointF *aPoint);
    void paintEvent(QPaintEvent *e);

};

#endif // POINCAREVIEW_H
