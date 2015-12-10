//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"
#include "Gaming.h"
namespace Gaming {
    Simple::Simple(const Game &g, const Position &p, double energy) {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        Agent::print(os);
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        return Agent::takeTurn(surr);
    }

}