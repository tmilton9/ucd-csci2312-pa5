//
// Created by Travis Milton on 12/10/15.
//
#include "Piece.h"

namespace Gaming
{
Piece::Piece(const Game &g, const Position &p, const Game &__game) : __game(__game) {

    setPosition(p);

}

Gaming::Piece::~Piece() {

}

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        return os;
    }
}