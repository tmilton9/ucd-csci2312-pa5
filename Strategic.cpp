//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"

#include "Strategic.h"
namespace Gaming {
    const char Strategic::STRATEGIC_ID = 'T';
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s): Agent(g, p, energy) {
    __strategy = s;
    }

    Strategic::~Strategic() {

    }

    void Strategic::print(std::ostream &os) const {
        Agent::print(os);
    }

    ActionType Gaming::Strategic::takeTurn(const Surroundings &s) const {

        Surroundings surr;
        return Agent::takeTurn(surr);
    }
}