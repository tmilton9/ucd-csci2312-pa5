//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
#include "Food.h"
namespace Gaming {
	const char Food::FOOD_ID = 'F';

	//************************************************************************************
	// Method:    Food
	// FullName:  Gaming::Food::Food
	// Access:    public
	// Returns:
	// Qualifier: : Resource( g, p, capacity)
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: double capacity
	//************************************************************************************
	Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {
	}

	//************************************************************************************
	// Method:    ~Food
	// FullName:  Gaming::Food::~Food
	// Access:    public
	// Returns:
	// Qualifier:
	//************************************************************************************
	Food::~Food() {
	}

	//************************************************************************************
	// Method:    print
	// FullName:  Gaming::Food::print
	// Access:    public
	// Returns:   void
	// Qualifier: const
	// Parameter: std::ostream & os
	// Info:      top level print function that provides the ID and id number back to game
	//************************************************************************************
	void Food::print(std::ostream &os) const { //TODO
		os << FOOD_ID << __id;
	}
}