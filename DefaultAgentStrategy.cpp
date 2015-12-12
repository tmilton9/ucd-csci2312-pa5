//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "DefaultAgentStrategy.h"
namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() {

    }

    DefaultAgentStrategy::~DefaultAgentStrategy() {

    }

    ActionType Gaming::DefaultAgentStrategy::operator()(
            const Surroundings &s) const {
     return S;
    }
}