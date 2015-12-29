//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "DefaultAgentStrategy.h"
#include "Game.h"

namespace Gaming {
	//****************************************************************************************
	// Method:    DefaultAgentStrategy
	// FullName:  Gaming::DefaultAgentStrategy::DefaultAgentStrategy
	// Access:    public
	// Returns:
	// Qualifier:
	//****************************************************************************************
	DefaultAgentStrategy::DefaultAgentStrategy() {
	}

	//****************************************************************************************
	// Method:    ~DefaultAgentStrategy
	// FullName:  Gaming::DefaultAgentStrategy::~DefaultAgentStrategy
	// Access:    public
	// Returns:
	// Qualifier:
	//****************************************************************************************
	DefaultAgentStrategy::~DefaultAgentStrategy() {
	}

	//****************************************************************************************
	// Method:    operator()
	// FullName:  Gaming::DefaultAgentStrategy::operator()
	// Access:    public
	// Returns:   Gaming::ActionType
	// Qualifier: const
	// Parameter: const Surroundings & s
	// Info:      function for overloaded ( ) operator that controls the Strategy function of
	//            the Strategic Agent and allows the system to use the correct behaviors
	//            the Default Agent should go after a Advantage first a Food if none
	//            are available or attack a Simple if no Resources are available
	//            if none of those are aavailable then it will move to an empty space or stay
	//****************************************************************************************
	ActionType Gaming::DefaultAgentStrategy::operator()(const Surroundings &s) const {
		int              desiredPosition = -1;                             // return value
		std::vector<int> AdvantageList;                                    // vector of Advantages
		std::vector<int> FoodList;                                         // vector of Food
		std::vector<int> SimpleList;                                       // vector of Simples
		std::vector<int> EmptyList;                                        // Vector of Empty

		for (int n = 0; n < s.array.size(); n++)                           // loop through positions
		{
			int temp = n;                                                  // set to proper list
			if (s.array[n] == ADVANTAGE) { AdvantageList.push_back(temp); }
			if (s.array[n] == FOOD) { FoodList.push_back(temp); }
			if (s.array[n] == SIMPLE) { SimpleList.push_back(temp); }
			if (s.array[n] == EMPTY) { EmptyList.push_back(temp); }
		}
		if (!EmptyList.empty())                                            // if there are empty spaces
		{ desiredPosition = EmptyList[rand() % EmptyList.size()]; }        // pick an empty pos
		if (!SimpleList.empty())                                           // if there are Simples
		{ desiredPosition = SimpleList[rand() % SimpleList.size()]; }      // pick a Simple to Attack
		if (!FoodList.empty())                                             // if there is food
		{ desiredPosition = FoodList[rand() % FoodList.size()]; }          // pick a food instead
		if (!AdvantageList.empty())                                        // if there is an advantage
		{ desiredPosition = AdvantageList[rand() % AdvantageList.size()]; }// pick one instead
		if (desiredPosition == 4) {                                        // if desired location is where we are
			if (EmptyList.size() > 1) {                                    // make sure that it is the only possibility
				desiredPosition = EmptyList[1];
			}                                                              // otherwise pick the next one
		}                                                                  // convert number to ActionType
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
}