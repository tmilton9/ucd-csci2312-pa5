//
// Created by Travis Milton on 12/10/15.
//

#include "Piece.h"
#include "Agent.h"


namespace Gaming {
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p, Game()) {
        __energy = energy;
    }

    Agent::~Agent() {

    }

    void Agent::age() {

    }

    Piece &Agent::operator*(Piece &other) {
        /* As Pieces move around the grid they run into others.
         * Each time that happens there is an interaction taking place.
         * This is captured by the pure virtual operator* (aka interaction operator)
         * that Piece-s overload. The interactions are as follows:
         * When an Agent moves onto a Resource, it consumes it completely.
         * When an Agent moves onto an Agent, they compete and might either both die,
         * or one dies and the other wins.
         */


        return *this;
    }

    Piece &Agent::interact(Agent *agent) {
        return *this;
    }

    Piece &Agent::interact(Resource *resource) {
        return *this;
    }


    ActionType Agent::takeTurn(const Surroundings &surr) const {
        return S;
    }

    void Agent::print(std::ostream &os) const {

    }


    PieceType Agent::getType() const {
        return STRATEGIC;
    }
}