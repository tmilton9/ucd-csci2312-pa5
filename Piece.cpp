//
// Created by Travis Milton on 12/10/15.
//
#include "Piece.h"

namespace Gaming
{
    std::vector<Piece *> __grid;
 unsigned int Piece::__idGen = 0;
Piece::Piece(const Game &g, const Position &p, const Game &__game) : __game(__game) {

    __position = p;
	__id = __idGen++;
    __turned = false;
    __finished = false;

}

Gaming::Piece::~Piece() {

}

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {//TODO
        piece.print(os);

        return os;
    }
}