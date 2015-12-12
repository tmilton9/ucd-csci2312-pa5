//
// Created by Travis Milton on 12/10/15.
//


#include "Piece.h"
#include "Resource.h"
namespace Gaming{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

PieceType Resource::getType() const {
    return STRATEGIC;
}

Resource::Resource( const Game &g, const Position &p, double __capacity) : Piece(g, p, Game()) {
    __capacity = __capacity;

}

Resource::~Resource() {

}

double Resource::consume() {
    return 0;
}

void Resource::age() {

}

ActionType Resource::takeTurn(const Surroundings &s) const {
    return S;
}

Piece &Resource::operator*(Piece &other) {
    return *this;
}

Piece &Resource::interact(Agent *agent) {
    return *this;
}

Piece &Resource::interact(Resource *resource) {
    return *this;
}

void Resource::print(std::ostream &os) const {

}
}