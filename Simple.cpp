//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"
#include "Simple.h"

namespace Gaming {
	const char Simple::SIMPLE_ID = 'S';

	//**************************************************************************************
	// Method:    Simple
	// FullName:  Gaming::Simple::Simple
	// Access:    public
	// Returns:
	// Qualifier: : Agent( g, p, energy)
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: double energy
	//**************************************************************************************
	Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) {
	}

	//**************************************************************************************
	// Method:    ~Simple
	// FullName:  Gaming::Simple::~Simple
	// Access:    public
	// Returns:
	// Qualifier:
	//**************************************************************************************
	Simple::~Simple() {
	}

	//**************************************************************************************
	// Method:    print
	// FullName:  Gaming::Simple::print
	// Access:    public
	// Returns:   void
	// Qualifier: const
	// Parameter: std::ostream & os
	// Info:      top level print function that provides the ID and id number back to game
	//**************************************************************************************
	void Simple::print(std::ostream &os) const {//TODO
		os << SIMPLE_ID << __id;
	}

	//**************************************************************************************
	// Method:    takeTurn
	// FullName:  Gaming::Simple::takeTurn
	// Access:    public
	// Returns:   Gaming::ActionType
	// Qualifier: const
	// Parameter: const Surroundings & s
	// Info:      this function controls the turn taking behavior of the Simple Agent
	//            it never attacks, it goes after Advantages and Food, if none will move
	//            to empty position else stay put
	//**************************************************************************************
	ActionType Simple::takeTurn(const Surroundings &s) const {

		int              desiredPosition = -1;                  // return value
		std::vector<int> AdvantageList;                         // vector of where Advantages are
		std::vector<int> FoodList;                              // vector of where Food is
		std::vector<int> EmptyList;                             // vector of empty positions.

		for (int n = 0; n < s.array.size(); n++) {              // loop for the surroundings array
			int temp = n;
			if (s.array[n] == ADVANTAGE) {                      // if Advantage
				AdvantageList.push_back(temp); }                // add to Resource pos array
			if (s.array[n] == FOOD){                            // if Food
				FoodList.push_back(temp); }                     // add to Food pos array
			if (s.array[n] == EMPTY) {                          // if empty
				EmptyList.push_back(temp); }                    // add to Empty pos array
		}
		if (AdvantageList.empty() && EmptyList.empty() && FoodList.empty()){        // if both arrays stay empty then dont mov
			return STAY; }
		else if (!AdvantageList.empty()) {                           // if there are Advantages pick one
			desiredPosition = AdvantageList[rand() % AdvantageList.size()]; }
		else if (!FoodList.empty()){                                 // if food pick one
			desiredPosition = FoodList[rand() % FoodList.size()]; }
		else {                                                  // if not then pick an empty location
			if (!EmptyList.empty())                             // if there are empty positions available pick one
			{ desiredPosition = EmptyList[rand() % EmptyList.size()]; }
		}
		if (desiredPosition == 4) {                             // if it picks 4 (where it already is) then
			if (EmptyList.size() < 1) {                         // check for other positions
				desiredPosition = EmptyList[1];
			}                                                   // if there are then pick the next one
		}                                                       // if statements to convert number to ActionType
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