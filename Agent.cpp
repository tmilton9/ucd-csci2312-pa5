//
// Created by Travis Milton on 12/10/15.
//

#include "Piece.h"
#include "Agent.h"
#include "Resource.h"
#include "Food.h"
#include "Advantage.h"
#include "Simple.h"

namespace Gaming {
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p, Game(g)) {
        __energy = energy;
    }

    Agent::~Agent() {

    }

    void Agent::age() {
        this->__energy =   AGENT_FATIGUE_RATE /   this->__energy;
        if (__energy < 2){finish();}
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


        if(other.getType() == STRATEGIC) {
            Agent *agent;
            agent = dynamic_cast<Agent *>(&other);
            this->interact(agent);

        }
        if(other.getType() == SIMPLE) {
            Simple *S;
            S = dynamic_cast<Simple *>(&other);
            this->interact(S);

        }
        if(other.getType() == FOOD){
            Food *F;
            F = dynamic_cast<Food *>(&other);
            this->interact(F);

        }
        if(other.getType() == ADVANTAGE){
            Advantage *A;
            A = dynamic_cast<Advantage *>(&other);
            this->interact(A);

        }
         return *this;
    }

    Piece &Agent::interact(Agent *agent) {
        this->__energy -= agent->__energy;
        if(this->__energy > 0){
            this->setPosition(agent->getPosition());
            if (agent->__energy <= 0){
                agent->finish(); }
        }
        if(this->__energy <= 0){
            finish();

        }
        return *this;
    }

    Piece &Agent::interact(Resource *resource) {
        if(resource->getType() == FOOD)  {
        addEnergy(resource->consume()); }
        if(resource->getType() == ADVANTAGE){
            addEnergy(this->__energy * resource->consume()); }
        this->setPosition(resource->getPosition());
        return *this;
    }


}