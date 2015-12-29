//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {
	const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

	//****************************************************************************************
	// Method:    AggressiveAgentStrategy
	// FullName:  Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy
	// Access:    public
	// Returns:
	// Qualifier:
	// Parameter: double agentEnergy
	//****************************************************************************************
	AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
		__agentEnergy = agentEnergy;
	}

	//****************************************************************************************
	// Method:    ~AggressiveAgentStrategy
	// FullName:  Gaming::AggressiveAgentStrategy::~AggressiveAgentStrategy
	// Access:    public
	// Returns:
	// Qualifier:
	//****************************************************************************************
	AggressiveAgentStrategy::~AggressiveAgentStrategy() {
	}

	//****************************************************************************************
	// Method:    operator()
	// FullName:  Gaming::AggressiveAgentStrategy::operator()
	// Access:    public
	// Returns:   Gaming::ActionType
	// Qualifier: const
	// Parameter: const Surroundings & s
	// Info:      function implementing Agressive strategy using overloaded () call from
	//            Strategic  this strategy Attacks first if over the threshold then procedes
	//            gather resources or move to an empty slot
	//****************************************************************************************
	ActionType Gaming::AggressiveAgentStrategy::operator()(const Surroundings &s) const {
		int              desiredPosition;
		std::vector<int> AgentList;                                 // vector arrays for holding Piece types
		std::vector<int> AdvantageList;
		std::vector<int> FoodList;
		std::vector<int> EmptyList;
		Position         CenterPos(1, 1);

		for (int i = 0; i < 9; i++) {                               // scan array for Pieces and sort accordingly
			if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC) { AgentList.push_back(i); }
			if (s.array[i] == ADVANTAGE) { AdvantageList.push_back(i); }
			if (s.array[i] == FOOD) { FoodList.push_back(i); }
			if (s.array[i] == EMPTY) { EmptyList.push_back(i); }
		}                                                           // if above attack
		if (__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD && AgentList.size() > 0) {
			return Game::reachSurroundings(CenterPos, Game::randomPosition(AgentList));
		} else if (!AdvantageList.empty()) {                        // if Advantage available
			return Game::reachSurroundings(CenterPos, Game::randomPosition(AdvantageList));
		} else if (!FoodList.empty()) {                             // else if Food available
			return Game::reachSurroundings(CenterPos, Game::randomPosition(FoodList));
		} else if (!EmptyList.empty()) {                            // else any empty positions
			desiredPosition = EmptyList[rand() % EmptyList.size()]; // pick an empty pos
			if (desiredPosition == 4) {
				desiredPosition = EmptyList[1];
			}                                                       // otherwise pick the next one
			if (desiredPosition == 0) return NW;
			if (desiredPosition == 1) return N;
			if (desiredPosition == 2) return NE;
			if (desiredPosition == 3) return W;
			if (desiredPosition == 4) return STAY;
			if (desiredPosition == 5) return E;
			if (desiredPosition == 6) return SW;
			if (desiredPosition == 7) return S;
			if (desiredPosition == 8) return SE;
		}
		else {                                                        // if all are 0 Stay
			return STAY;
		}

	}
}