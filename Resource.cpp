//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "Piece.h"
namespace Gaming{
Gaming::PieceType Gaming::Resource::getType() const {
    return INACCESSIBLE;
}

Gaming::Resource::Resource(const ::Gaming::Resource::Game &g, const ::Gaming::Resource::Position &p,
                           double __capacity) {

}

Gaming::Resource::~Resource() {

}

double Gaming::Resource::consume() {
    return 0;
}

void Gaming::Resource::age() {

}

Gaming::ActionType Gaming::Resource::takeTurn(const ::Gaming::Resource::Surroundings &s) const {
    return S;
}

Gaming::Piece &Gaming::Resource::operator*(::Gaming::Resource::Piece &other) {
    return <#initializer#>;
}

Gaming::Piece &Gaming::Resource::interact(::Gaming::Resource::Agent *agent) {
    return <#initializer#>;
}

Gaming::Piece &Gaming::Resource::interact(::Gaming::Resource::Resource *resource) {
    return <#initializer#>;
}

void Gaming::Resource::print(std::ostream &os) const {

}
}