//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
#include "Advantage.h"

namespace Gaming {
	const char   Advantage::ADVANTAGE_ID          = 'D';
	const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

	//**************************************************************************************
	// Method:    Advantage
	// FullName:  Gaming::Advantage::Advantage
	// Access:    public
	// Returns:
	// Qualifier: :Resource(g, p, capacity)
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: double capacity
	//**************************************************************************************
	Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {
		__capacity = capacity * ADVANTAGE_MULT_FACTOR;
	}

	//**************************************************************************************
	// Method:    ~Advantage
	// FullName:  Gaming::Advantage::~Advantage
	// Access:    public
	// Returns:
	// Qualifier:
	//**************************************************************************************
	Advantage::~Advantage() {
	}

	//**************************************************************************************
	// Method:    print
	// FullName:  Gaming::Advantage::print
	// Access:    public
	// Returns:   void
	// Qualifier: const
	// Parameter: std::ostream & os
	// Info:      top level print function that provides the ID and id number back to game
	//**************************************************************************************
	void Advantage::print(std::ostream &os) const { //TODO
		os << ADVANTAGE_ID << __id;
	}

	//**************************************************************************************
	// Method:    getCapacity
	// FullName:  Gaming::Advantage::getCapacity
	// Access:    public
	// Returns:   double
	// Qualifier: const
	// Info:      returns capacity to caller
	//**************************************************************************************
	double Advantage::getCapacity() const {
		return __capacity;
	}

	//**************************************************************************************
	// Method:    consume
	// FullName:  Gaming::Advantage::consume
	// Access:    public
	// Returns:   double
	// Qualifier:
	// Info:      returns capacity to the Agent consuming the Resource
	//**************************************************************************************
	double Advantage::consume() {
		Piece::finish();
		return __capacity;
	}
}