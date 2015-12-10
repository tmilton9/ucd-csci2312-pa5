//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_AGENT_H
#define PA5GAME_AGENT_H

#include "Game.h"
#include "Piece.h"

namespace Gaming {

    class Agent : public Piece {

    protected:
        double __energy;

    public:
        static const double AGENT_FATIGUE_RATE;

        virtual PieceType getType() const override ;

        virtual ActionType takeTurn(const Surroundings &surr) const override ;

    protected:
        virtual void print(std::ostream &os) const override ;

        Agent(const Game &g, const Position &p, double energy);
        ~Agent();

        double getEnergy() const { return __energy; }
        void addEnergy(double e) { __energy += e; }

        void age() override final;

        bool isViable() const override final { return !isFinished() && __energy > 0.0; }

        Piece &operator*(Piece &other) override final;
        Piece &interact(Agent *) override final;
        Piece &interact(Resource *) override final;

    };

}


#endif //PA5GAME_AGENT_H
