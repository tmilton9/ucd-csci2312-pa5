//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"

#include "Simple.h"
namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';
    Simple::Simple(const Game &g, const Position &p, double energy)
            : Agent( g, p, energy) {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        Agent::print(os);
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        Surroundings surr;
        return Agent::takeTurn(surr);
    }

}