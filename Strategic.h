//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_STRATEGIC_H
#define PA5GAME_STRATEGIC_H

#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming {
	class AggressiveAgentStrategy;
	class DefaultAgentStrategy;
	class Strategic : public Agent {
	private:
		static const char STRATEGIC_ID;

		Strategy *__strategy;

	public:

		Strategic(const Game &g, const Position &p, double energy, Strategy *s = new DefaultAgentStrategy());
		~Strategic();
		double Agg;
		PieceType getType() const override { return PieceType::STRATEGIC; }

		void print(std::ostream &os) const override;

		ActionType takeTurn(const Surroundings &s) const override;
	};
}

#endif //PA5GAME_STRATEGIC_H
