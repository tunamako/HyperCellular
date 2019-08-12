#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QVector>

#include "include/pcviewmodel.h"
#include "include/tile.h"


class Automaton {
 public:
    Automaton();
    virtual ~Automaton();

    void clicked(Tile *aTile);
    void randomize(QVector<Tile*> *aTileList);
    void fill(QVector<Tile*> *aTileList);
    virtual void nextGeneration(PoincareViewModel *);
};

class WireWorld : public Automaton {
 public:
    WireWorld();
    virtual ~WireWorld();

    virtual void nextGeneration(PoincareViewModel *model);
};

class Life : public Automaton {
 public:
    Life();
    virtual ~Life();

    virtual void nextGeneration(PoincareViewModel *model);
};

#endif // AUTOMATON_H