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

class Tile;

namespace Ui {
class PoincareViewModel;
}

class PoincareViewModel : public QWidget {
 public:
    static PoincareViewModel* getInstance();
    static PoincareViewModel* getInstance(QWidget *parent);

    int adjacentCount;
    int sideCount;
    int renderDepth;
    bool fillMode;
    float diskDiameter;
    QPainter *painter;
    QPointF origin;
    QRegion diskRegion;
    QVector<Tile *> tiles;

    int setSideCount(int count);
    int setAdjCount(int count);
    void setRenderDepth(int depth);

    void toggleFillMode();
    void updateTiles();

    bool tileExists(QPointF tileCenter);
    void addTile(Tile *aTile);

 private:
    explicit PoincareViewModel(QWidget *parent);

    static PoincareViewModel* m_pInstance;
    bool tilesToUpdate;
    int drawnCount;
    QWidget *parent;
    Tile *centerTile = nullptr;
    QPainterPath diskPath;

    std::map<float, std::unordered_set<float> > drawnTiles;

    void drawTiling();
    QVector<QPointF> genCenterVertices();
    void paintEvent(QPaintEvent *);
    bool areHyperbolicDims(int p, int q);
    // void mousePressEvent();
};

#endif // POINCAREVIEW_H
