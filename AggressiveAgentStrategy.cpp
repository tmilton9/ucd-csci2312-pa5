//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
namespace Gaming {
    Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {

    }

    Gaming::AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    Gaming::ActionType Gaming::AggressiveAgentStrategy::operator()(
            const ::Gaming::AggressiveAgentStrategy::Surroundings &s) const {
        return S;
    }
}