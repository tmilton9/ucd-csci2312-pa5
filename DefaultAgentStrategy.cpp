//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
namespace Gaming {
    Gaming::DefaultAgentStrategy::DefaultAgentStrategy() {

    }

    Gaming::DefaultAgentStrategy::~DefaultAgentStrategy() {

    }

    Gaming::ActionType Gaming::DefaultAgentStrategy::operator()(
            const ::Gaming::DefaultAgentStrategy::Surroundings &s) const {
     return S;
    }
}