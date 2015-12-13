//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"

#include "Simple.h"
#include "Game.h"
namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';
    Simple::Simple(const Game &g, const Position &p, double energy)
            : Agent( g, p, energy) {
    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        Agent::print(os);
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        bool good = false;
        Position P;
        ActionType A;

        while (!good) {
            P = __game.randomPosition((const std::vector<int> &) s.array);
            A = __game.reachSurroundings(this->getPosition(), P);
            switch (A) {
                case N: {
                    if (s.array[1] == ADVANTAGE){good = true;}
                    if (s.array[1] == FOOD){good = true;}
                    if (s.array[1] != STRATEGIC) {
                        if (s.array[1] != SIMPLE) { good = true; }
                    }break;
                }
                case NE: {
                    if (s.array[2] == ADVANTAGE){good = true;}
                    if (s.array[2] == FOOD){good = true;}
                    if (s.array[2] != STRATEGIC) {
                        if (s.array[2] != SIMPLE) { good = true; }
                    }break;
                }
                case NW: {
                    if (s.array[0] == ADVANTAGE){good = true;}
                    if (s.array[0] == FOOD){good = true;}
                    if (s.array[0] != STRATEGIC) {
                        if (s.array[0] != SIMPLE) { good = true; }
                    }break;
                }
                case E: {
                    if (s.array[5] == ADVANTAGE){good = true;}
                    if (s.array[5] == FOOD){good = true;}
                    if (s.array[5] != STRATEGIC) {
                        if (s.array[5] != SIMPLE) { good = true; }
                    }break;
                }
                case W: {
                    if (s.array[3] == ADVANTAGE){good = true;}
                    if (s.array[3] == FOOD){good = true;}
                    if (s.array[3] != STRATEGIC) {
                        if (s.array[3] != SIMPLE) { good = true; }
                    }break;
                }
                case SE: {
                    if (s.array[8] == ADVANTAGE){good = true;}
                    if (s.array[8] == FOOD){good = true;}
                    if (s.array[8] != STRATEGIC) {
                        if (s.array[8] != SIMPLE) { good = true; }
                    }break;
                }
                case SW: {
                    if (s.array[6] == ADVANTAGE){good = true;}
                    if (s.array[6] == FOOD){good = true;}
                    if (s.array[6] != STRATEGIC) {
                        if (s.array[6] != SIMPLE) { good = true; }
                    }break;
                }
                case S: {
                    if (s.array[7] == ADVANTAGE){good = true;}
                    if (s.array[7] == FOOD){good = true;}
                    if (s.array[7] != STRATEGIC) {
                        if (s.array[7] != SIMPLE) { good = true; }
                    }break;
                }
                case STAY:
                    good = true;
                    break;
            }


        }
        return A;
    }

}