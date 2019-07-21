#ifndef POINCAREVIEW_H
#define POINCAREVIEW_H

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPointF>
#include <QRegion>
#include <QVector>
#include <QWidget>

#include <string>
#include <map>
#include <unordered_set>

#include "include/tile.h"


namespace Ui {
class PoincareViewModel;
}

class PoincareViewModel : public QWidget {
 public:
    int adjacentCount;
    int sideCount;
    int renderDepth;
    QVector<Tile *> *tiles;

    explicit PoincareViewModel(QWidget *parent);
    virtual ~PoincareViewModel();

    int setSideCount(int count);
    int setAdjCount(int count);
    void setRenderDepth(int depth);

    void toggleFillMode();
    void updateTiles();

 private:
    bool fillMode;
    bool tilesToUpdate;
    float diskDiameter;
    int drawnCount;

    QWidget *parent;
    QVector<QPointF> centerVertices;
    QPainterPath *diskPath;
    QRegion *diskRegion;
    QPainter *painter;
    QPointF *origin;

    std::map<float, std::unordered_set<float> > drawnTiles;

    void drawTiling();
    void genCenterVertices();
    bool hasBeenDrawn(QPointF *aPoint);
    void addDrawnTile(Tile *aTile);
    void paintEvent(QPaintEvent *e);
    bool areHyperbolicDims(int p, int q);
    // void mousePressEvent();
};

#endif // POINCAREVIEW_H
