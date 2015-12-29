//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"

#include "Strategic.h"

namespace Gaming {
	const char Strategic::STRATEGIC_ID = 'T';

	//****************************************************************************************
	// Method:    Strategic
	// FullName:  Gaming::Strategic::Strategic
	// Access:    public
	// Returns:
	// Qualifier: : Agent(g, p, energy)
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: double energy
	// Parameter: Strategy * s
	//****************************************************************************************
	Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy) {
		__strategy = s;

		Agg = energy *0.75;
	}

	//****************************************************************************************
	// Method:    ~Strategic
	// FullName:  Gaming::Strategic::~Strategic
	// Access:    public
	// Returns:
	// Qualifier:
	//****************************************************************************************
	Strategic::~Strategic() {
		__strategy = nullptr;
	}

	//****************************************************************************************
	// Method:    print
	// FullName:  Gaming::Strategic::print
	// Access:    public
	// Returns:   void
	// Qualifier: const
	// Parameter: std::ostream & os
	// Info:      top level print function that provides the ID and id number back to game
	//****************************************************************************************
	void Strategic::print(std::ostream &os) const {//TODO
		os << STRATEGIC_ID << __id;
	}

	//****************************************************************************************
	// Method:    takeTurn
	// FullName:  Gaming::Strategic::takeTurn
	// Access:    public
	// Returns:   Gaming::ActionType
	// Qualifier: const
	// Parameter: const Surroundings & s
	// Info:      call that uses overloaded ( ) to call the strategy for the Strategic Agent
	//****************************************************************************************
	ActionType Gaming::Strategic::takeTurn(const Surroundings &s) const {
		return (*__strategy)(s);
	}
}