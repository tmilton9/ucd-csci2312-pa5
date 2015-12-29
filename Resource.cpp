//
// Created by Travis Milton on 12/10/15.
//

#include "Piece.h"
#include "Resource.h"
#include "Agent.h"

namespace Gaming {
	const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

	//*****************************************************************************************
	// Method:    Resource
	// FullName:  Gaming::Resource::Resource
	// Access:    public
	// Returns:
	// Qualifier: : Piece(g, p, Game(g))
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: double capacity
	//*****************************************************************************************
	Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p, Game(g)) {
		__capacity = capacity;
	}

	//*****************************************************************************************
	// Method:    ~Resource
	// FullName:  Gaming::Resource::~Resource
	// Access:    public
	// Returns:
	// Qualifier:
	//*****************************************************************************************
	Resource::~Resource() {
	}

	//*****************************************************************************************
	// Method:    consume
	// FullName:  Gaming::Resource::consume
	// Access:    virtual public
	// Returns:   double
	// Qualifier:
	// Info:      sets the item to be finished true with the finish call and returns capacity
	//*****************************************************************************************
	double Resource::consume() {
		finish();
		return __capacity;
	}

	//*****************************************************************************************
	// Method:    age
	// FullName:  Gaming::Resource::age
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Info:      ages the Resource by subtracting the spoil factor from the capacity
	//*****************************************************************************************
	void Resource::age() {
		__capacity = __capacity - RESOURCE_SPOIL_FACTOR;
		if (__capacity < .00001) { finish(); }
	}

	//*****************************************************************************************
	// Method:    takeTurn
	// FullName:  Gaming::Resource::takeTurn
	// Access:    public
	// Returns:   Gaming::ActionType
	// Qualifier: const
	// Parameter: const Surroundings & s
	// info:      always returns true because resources cant move
	//*****************************************************************************************
	ActionType Resource::takeTurn(const Surroundings &s) const {
		return STAY;
	}

	//*****************************************************************************************
	// Method:    operator*
	// FullName:  Gaming::Resource::operator*
	// Access:    public
	// Returns:   Piece &
	// Qualifier:
	// Parameter: Piece & other
	// Info:      allows Peices to interact with eachother using the * operator
	//*****************************************************************************************
	Piece &Resource::operator*(Piece &other) {
		other.interact(this);                       // calls interact function or the Agent
		return *this;
	}

	//*****************************************************************************************
	// Method:    interact
	// FullName:  Gaming::Resource::interact
	// Access:    public
	// Returns:   Piece &
	// Qualifier:
	// Parameter: Agent * agent
	// Info:      cleans up the reasource after being consumed
	//*****************************************************************************************
	Piece &Resource::interact(Agent *agent) {
		this->finish();                             // calls finish function to set finished flag
		return *this;
	}

	//*****************************************************************************************
	// Method:    interact
	// FullName:  Gaming::Resource::interact
	// Access:    public
	// Returns:   Piece &
	// Qualifier:
	// Parameter: Resource * resource
	// Info:      just returns this because Resources cant interact
	//*****************************************************************************************
	Piece &Resource::interact(Resource *resource) {
		return *this;
	}
}