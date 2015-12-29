//
// Created by Travis Milton on 12/10/15.
//

#include "Piece.h"
#include "Agent.h"
#include "Resource.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {
	const double Agent::AGENT_FATIGUE_RATE = 0.3;

	//*****************************************************************************************
	// Method:    Agent
	// FullName:  Gaming::Agent::Agent
	// Access:    public
	// Returns:
	// Qualifier: : Piece(g, p, Game(g))
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: double energy
	//*****************************************************************************************
	Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p, Game(g)) {
		__energy = energy;
	}

	//*****************************************************************************************
	// Method:    ~Agent
	// FullName:  Gaming::Agent::~Agent
	// Access:    public
	// Returns:
	// Qualifier:
	//*****************************************************************************************
	Agent::~Agent() {
	}

	//*****************************************************************************************
	// Method:    age
	// FullName:  Gaming::Agent::age
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Info:      ages the Agent by subtracting its energy from the fatigue rate
	//*****************************************************************************************
	void Agent::age() {
		__energy = __energy - AGENT_FATIGUE_RATE;
		if (__energy < 0.0001) { finish(); }                //calls finish function to set finished
	}

	//*****************************************************************************************
	// Method:    operator*
	// FullName:  Gaming::Agent::operator*
	// Access:    public
	// Returns:   Piece &
	// Qualifier:
	// Parameter: Piece & other
	// Info:      overload of the * operator that allows the Agents to interact with other Pieces
	//*****************************************************************************************
	Piece &Agent::operator*(Piece &other) {
		Piece *agent = dynamic_cast<Agent *>(&other);
		if (agent) {                                           // if the other Piece is an Agent
			return interact(dynamic_cast<Agent *>(&other));
		}


		Piece *resource = dynamic_cast<Resource *>(&other);
		if (resource) {                                        // if the other Piece is a Resource
			return interact(dynamic_cast<Resource *>(&other));
		}

	}

	//*****************************************************************************************
	// Method:    interact
	// FullName:  Gaming::Agent::interact
	// Access:    public
	// Returns:   Piece &
	// Qualifier:
	// Parameter: Agent * agent
	// Info:      function that facilitates the interaction between Agents and handles the
	//            transfer and finish flagging
	//*****************************************************************************************
	Piece &Agent::interact(Agent *agent) {
		if (__energy > agent->__energy) {                   // if the attacker is stronger
			__energy -= agent->__energy;                    // subtract the others energy from attacker
			agent->__energy = 0;                            // set other energy to 0
			agent->finish();                                // set other finished
		}
		else if (__energy == agent->__energy) {             // if the attacker is equal
			__energy = 0;                                   // set both Agents to 0 energy
			agent->__energy = 0;
			agent->finish();                                // set both finished
			finish();
		}
		else {                                              // if the attacker is weaker
			agent->__energy -= __energy;                    // subtract attackers energy from others
			__energy = 0;                                   // set attacker to 0 energy
			finish();                                       // set attacker finished
		}

		return *this;
	}

	//*****************************************************************************************
	// Method:    interact
	// FullName:  Gaming::Agent::interact
	// Access:    public
	// Returns:   Piece &
	// Qualifier:
	// Parameter: Resource * resource
	// Info:      function to facilitate energy transfer to Agent from Resource
	//*****************************************************************************************
	Piece &Agent::interact(Resource *resource) {
		Resource *food = dynamic_cast<Food *>(resource);
		if (food) {                                         // if Food
			this->addEnergy(food->consume());               // consume
			resource->interact(this);                       // call Resource version to cleanup
		}

		Resource *advantage = dynamic_cast<Advantage *>(resource);
		if (advantage) {                                    // if Advantage
			this->addEnergy(advantage->consume());          // consume
			resource->interact(this);                       // call Resource version to cleanup
		}
		return *this;
	}
}