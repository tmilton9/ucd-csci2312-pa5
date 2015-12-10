//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"
#include "Gaming.h"
namespace Gaming {
    Strategic::Strategic(const Game &g, const Position &p,
                                 double energy,
                                 Strategy *s) {

    }

    Strategic::~Strategic() {

    }

    void Strategic::print(std::ostream &os) const {
        Agent::print(os);
    }

    Gaming::ActionType Gaming::Strategic::takeTurn(const Surroundings &s) const {
        return Agent::takeTurn(surr);
    }
}