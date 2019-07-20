#import "include/automaton.h"

Automaton::Automaton() {}
Automaton::~Automaton() {}
void Automaton::clicked(Tile *aTile) {
}
void Automaton::randomize(QVector<Tile*> *aTileList) {
}
void Automaton::fill(QVector<Tile*> *aTileList) {
}

void Automaton::nextGeneration(PoincareViewModel *model) {}


WireWorld::WireWorld() {}
WireWorld::~WireWorld() {}
void WireWorld::nextGeneration(PoincareViewModel *model) {}

Life::Life() {}
Life::~Life() {}
void Life::nextGeneration(PoincareViewModel *model) {}
