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
    int adjacentCount;
    int sideCount;
    int renderDepth;

    explicit PoincareViewModel(QWidget *parent);
    virtual ~PoincareViewModel();

    int setSideCount(int count);
    int setAdjCount(int count);
    void setRenderDepth(int depth);

protected:
    bool areHyperbolicDims(int p, int q);
    void toggleFillMode();
    void updateTiles();
    // void mousePressEvent();

private:
    bool fillMode;
    bool tilesToUpdate;
    int diskDiameter;
    int drawnCount;

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
