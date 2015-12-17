//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"

#include "Strategic.h"

namespace Gaming {
	const char Strategic::STRATEGIC_ID = 'T';
	Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy) {
		__strategy = s;

		Agg = energy *0.75;
	}

	Strategic::~Strategic() {
	}

	void Strategic::print(std::ostream &os) const {//TODO
        os << STRATEGIC_ID;


	}

	//************************************
	// Method:    takeTurn
	// FullName:  Gaming::Strategic::takeTurn
	// Access:    public 
	// Returns:   Gaming::ActionType
	// Qualifier: const
	// Parameter: const Surroundings & s
	//************************************
	ActionType Gaming::Strategic::takeTurn(const Surroundings &s) const {
		/*The default Strategic Agent's strategy (captured in a DefaultAgentStrategy object)
		 * is as follows: If there are adjacent Advantage-s, returns a motion to one of them.
		 * That is, it prefers Advantage to Food.lf there aren't adjacent Advantage-s,
		 * returns a move to an adjacent Food.If there arent' adjacent Food-s,
		 * return's a move to an adjacent empty position.If there aren't adjacent empty positions,
		 * it returns a move to an adjacent Simple agent (i.e. attacking it).
		 * If no adjacent Simple agents, returns STAY.
		 */
		 /*
		* The aggressive Strategic Agent's strategy (captured in an AggressiveAgentStrategy object)
		* is as follows:If the Agent's energy >= aggressiveness threshold AND there are any adjacent
		* Agent-s, challenge one of them.Else if adjacent Advantage-s, move onto an Advantage.                                                                                                                                         * Else if adjacent Food-s, move onto an Food.Else if adjacent empty positions,
		* move onto an empty position. Else STAY.
		*/

		bool good = false;
		Position P, O;
		O = this->getPosition();
		ActionType A;
		ActionType AT;
        std::vector<int> index{0, 1, 2, 3, 4, 5, 6, 7, 8};
		while (!good) {
            P = __game.randomPosition(index);
			AT = __strategy->operator()(s);
			if (AT !=STAY) { return AT; }
			A = __game.reachSurroundings(O, P);
			switch (A) {
            case N: {
                if (s.array[1] == ADVANTAGE) { good = true; }
                if (s.array[1] == FOOD) { good = true; }
                break;
            }
            case NE: {
                if (s.array[2] == ADVANTAGE) { good = true; }
                if (s.array[2] == FOOD) { good = true; }
                break;
            }
            case NW: {
                if (s.array[0] == ADVANTAGE) { good = true; }
                if (s.array[0] == FOOD) { good = true; }
                break;
            }
            case E: {
                if (s.array[5] == ADVANTAGE) { good = true; }
                if (s.array[5] == FOOD) { good = true; }
                break;
            }
            case W: {
                if (s.array[3] == ADVANTAGE) { good = true; }
                if (s.array[3] == FOOD) { good = true; }
                break;
            }
            case SE: {
                if (s.array[8] == ADVANTAGE) { good = true; }
                if (s.array[8] == FOOD) { good = true; }
                break;
            }
            case SW: {
                if (s.array[6] == ADVANTAGE) { good = true; }
                if (s.array[6] == FOOD) { good = true; }
                break;
            }
            case S: {
                if (s.array[7] == ADVANTAGE) { good = true; }
                if (s.array[7] == FOOD) { good = true; }
                break;
            }
            case STAY:
                good = true;
                break;
            }

		}
		return A;
	}
}