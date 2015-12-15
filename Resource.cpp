//
// Created by Travis Milton on 12/10/15.
//


#include "Piece.h"
#include "Resource.h"
namespace Gaming{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;


Resource::Resource( const Game &g, const Position &p, double capacity) : Piece(g, p, Game(g)) {
    __capacity = capacity;

}

Resource::~Resource() {

}

double Resource::consume() {
    finish();
    return __capacity;
}

void Resource::age() {
    this->__capacity = this->__capacity / RESOURCE_SPOIL_FACTOR;
    if (this->__capacity < 2){finish();}
}

ActionType Resource::takeTurn(const Surroundings &s) const {
    return STAY;
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


}