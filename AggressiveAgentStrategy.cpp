//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "AggressiveAgentStrategy.h"
#include "Game.h"
#include "Piece.h"

double STARTING_AGENT_ENERGY;
namespace Gaming {
	const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = STARTING_AGENT_ENERGY * 0.75;
	AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
		__agentEnergy = agentEnergy;
	}

	AggressiveAgentStrategy::~AggressiveAgentStrategy() {
	}

	ActionType Gaming::AggressiveAgentStrategy::operator()(const Surroundings &s) const {
		bool good = false;

		ActionType A;

			if (__agentEnergy > DEFAULT_AGGRESSION_THRESHOLD) {
				for (std::array<PieceType, 9>::const_iterator it = s.array.begin(); it != s.array.end(); ++it) {
					if(!good){
					if (s.array[*it] == STRATEGIC) {
						if (s.array[1] == STRATEGIC) { A = N; good = true; break;}
						if (s.array[2] == STRATEGIC) { A = NE; good = true; break;}
						if (s.array[0] == STRATEGIC) { A = NW; good = true; break;}
						if (s.array[5] == STRATEGIC) { A = E; good = true; break;}
						if (s.array[3] == STRATEGIC) { A = W; good = true; break;}
						if (s.array[8] == STRATEGIC) { A = SE; good = true; break;}
						if (s.array[6] == STRATEGIC) { A = SW; good = true; break;}
						if (s.array[7] == STRATEGIC) { A = S; good = true; break;}
					}
					}
				}
				if (!good){
				
				for (std::array<PieceType, 9>::const_iterator it = s.array.begin(); it != s.array.end(); ++it) {
					if (!good){
					if (s.array[*it] == SIMPLE) {
						if (s.array[1] == SIMPLE) { A = N; good = true; break;}
						if (s.array[2] == SIMPLE) { A = NE; good = true; break;}
						if (s.array[0] == SIMPLE) { A = NW; good = true; break;}
						if (s.array[5] == SIMPLE) { A = E; good = true; break;}
						if (s.array[3] == SIMPLE) { A = W; good = true; break;}
						if (s.array[8] == SIMPLE) { A = SE; good = true; break;}
						if (s.array[6] == SIMPLE) { A = SW; good = true; break;}
						if (s.array[7] == SIMPLE) { A = S; good = true; break;}
						
					}
				}
				}
				}
				if (good) {
					return A;
				}
			}
		


		return STAY;// not aggressive flag
	}
}