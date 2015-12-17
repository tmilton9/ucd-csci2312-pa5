//
// Created by Travis Milton on 12/10/15.
//
#include "Piece.h"

namespace Gaming {
    std::vector<Piece *> __grid;
    unsigned int Piece::__idGen = 0;

    Piece::Piece(const Game &g, const Position &p, const Game &__game) : __game(__game) {

        __position = p;
        __id = 0;
        __id = __idGen++;
        __turned = false;
        __finished = false;
        positioned = false;


    }

    Gaming::Piece::~Piece() {
        __idGen--;
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {//TODO

        piece.print(os);

        os << piece.__id;

        return os;
    };
}
