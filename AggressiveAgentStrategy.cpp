//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "AggressiveAgentStrategy.h"

double STARTING_AGENT_ENERGY;
namespace Gaming {
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = STARTING_AGENT_ENERGY * 0.75;
    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {

    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType Gaming::AggressiveAgentStrategy::operator()(
            const Surroundings &s) const {
        return S;
    }
}