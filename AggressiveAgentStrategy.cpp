//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "AggressiveAgentStrategy.h"
#include "Game.h"
#include "Piece.h"
#include ""

double STARTING_AGENT_ENERGY;
namespace Gaming {
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = STARTING_AGENT_ENERGY * 0.75;
    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        const double Aggression = DEFAULT_AGGRESSION_THRESHOLD;
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType Gaming::AggressiveAgentStrategy::operator()(const Surroundings &s) const {
       ActionType A;

        return A;
    }
}