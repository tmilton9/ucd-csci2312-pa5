//
// Created by Travis Milton on 12/10/15.
//

#include "Piece.h"
namespace Gaming {
    Agent::Agent(const Game &g, const Position &p, double energy) {

    }

    Agent::~Agent() {

    }

    void Agent::age() {

    }

    Piece &Agent::operator*(Piece &other) {
        return <#initializer#>;
    }

    Piece &Agent::interact(Agent *agent) {
        return <#initializer#>;
    }

    Piece &Agent::interact(Resource *resource) {
        return <#initializer#>;
    }

    PieceType Agent::getType() const {
        return INACCESSIBLE;
    }

    ActionType Agent::takeTurn(const Surroundings &surr) const {
        return S;
    }

    void Agent::print(std::ostream &os) const {

    }
}