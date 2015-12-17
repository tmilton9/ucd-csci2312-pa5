//
// Created by Travis Milton on 12/10/15.
//

#include "Gaming.h"
#include "DefaultAgentStrategy.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() {
    }

    DefaultAgentStrategy::~DefaultAgentStrategy() {
    }

    ActionType Gaming::DefaultAgentStrategy::operator()(const Surroundings &s) const {
		/*The default Strategic Agent's strategy (captured in a DefaultAgentStrategy object)
		* is as follows: If there are adjacent Advantage-s, returns a motion to one of them.
		* That is, it prefers Advantage to Food.lf there aren't adjacent Advantage-s,
		* returns a move to an adjacent Food.If there arent' adjacent Food-s,
		* return's a move to an adjacent empty position.If there aren't adjacent empty positions,
		* it returns a move to an adjacent Simple agent (i.e. attacking it).
		* If no adjacent Simple agents, returns STAY.
		*/
		bool good = false;

		ActionType A;


				for (std::array<PieceType,9>::const_iterator it = s.array.begin(); it != s.array.end(); ++it) {
                    if (!good){
					if (*it == ADVANTAGE) {
						if (s.array[1] == ADVANTAGE) {A = N; good = true; break;}
						if (s.array[2] == ADVANTAGE) { A = NE; good = true; break;}
						if (s.array[0] == ADVANTAGE) { A = NW; good = true; break;}
						if (s.array[5] == ADVANTAGE) { A = E; good = true; break;}
						if (s.array[3] == ADVANTAGE) { A = W; good = true; break;}
						if (s.array[8] == ADVANTAGE) { A = SE; good = true; break;}
						if (s.array[6] == ADVANTAGE) { A = SW; good = true; break;}
						if (s.array[7] == ADVANTAGE) { A = S; good = true; break;}
					}
                    }
				}
        if (!good) {
            for (std::array<PieceType,9>::const_iterator it = s.array.begin(); it != s.array.end(); ++it) {
                if (!good) {
                    if (s.array[*it] == FOOD) {
                        if (s.array[1] == FOOD) {
                            A = N;
                            good = true;
                            break;
                        }
                        if (s.array[2] == FOOD) {
                            A = NE;
                            good = true;
                            break;
                        }
                        if (s.array[0] == FOOD) {
                            A = NW;
                            good = true;
                            break;
                        }
                        if (s.array[5] == FOOD) {
                            A = E;
                            good = true;
                            break;
                        }
                        if (s.array[3] == FOOD) {
                            A = W;
                            good = true;
                            break;
                        }
                        if (s.array[8] == FOOD) {
                            A = SE;
                            good = true;
                            break;
                        }
                        if (s.array[6] == FOOD) {
                            A = SW;
                            good = true;
                            break;
                        }
                        if (s.array[7] == FOOD) {
                            A = S;
                            good = true;
                            break;
                        }
                        }
                    }
            }
            }
        if (!good) {
            for (std::array<PieceType, 9>::const_iterator it = s.array.begin(); it != s.array.end(); ++it) {
                if (!good) {
                    if (s.array[*it] == EMPTY) {
                        if (s.array[1] == EMPTY) {
                            A = N;
                            good = true;
                            break;
                        }
                        if (s.array[2] == EMPTY) {
                            A = NE;
                            good = true;
                            break;
                        }
                        if (s.array[0] == EMPTY) {
                            A = NW;
                            good = true;
                            break;
                        }
                        if (s.array[5] == EMPTY) {
                            A = E;
                            good = true;
                            break;
                        }
                        if (s.array[3] == EMPTY) {
                            A = W;
                            good = true;
                            break;
                        }
                        if (s.array[8] == EMPTY) {
                            A = SE;
                            good = true;
                            break;
                        }
                        if (s.array[6] == EMPTY) {
                            A = SW;
                            good = true;
                            break;
                        }
                        if (s.array[7] == EMPTY) {
                            A = S;
                            good = true;
                            break;
                        }
                    }
                }
            }
        }
        if(!good){
				for (std::array<PieceType, 9>::const_iterator it = s.array.begin(); it != s.array.end(); ++it) {
                    if (!good) {
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
		return STAY;// not aggressive flag
    }
}
