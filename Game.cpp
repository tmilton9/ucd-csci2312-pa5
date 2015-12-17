//
// Created by Travis Milton on 12/10/15.
//

#include "Game.h"
#include "Piece.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"


namespace Gaming {
	const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

	Gaming::PositionRandomizer Game::__posRandomizer;

	const unsigned Game::MIN_WIDTH = 3;
	const unsigned Game::MIN_HEIGHT = 3;
	const double Game::STARTING_AGENT_ENERGY = 20;
	const double Game::STARTING_RESOURCE_CAPACITY = 10;

	Game::Game(){
		__width = MIN_WIDTH;
		__height = MIN_HEIGHT;
		__round = 0;
		__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
		__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
		manual = true;
		__verbose = false;
		__grid.resize(__width * __height);


	}

	Game::Game(unsigned width, unsigned height, bool manual1)
			: manual(true) {
		__width = width;
		__height = height;
		__round = 0;
		__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
		__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
		manual = manual1;
		__grid.resize(__width * __height);


	}

	Game::Game(const Game &another) {
		__grid = another.__grid;
		__round = another.__round;
		manual = another.manual;
	}

	Game::~Game() {

	}

	unsigned int Game::getNumPieces() const {
		unsigned int numPieces = 0;
		for (int i = 0; i < sizeof(__grid); ++i) {
			if (__grid[i]->getType() == STRATEGIC)
				numPieces++;
			if (__grid[i]->getType() == SIMPLE)
				numPieces++;
			if (__grid[i]->getType() == FOOD)
				numPieces++;
			if (__grid[i]->getType() == ADVANTAGE)
				numPieces++;
		}
		return numPieces;
	}

	unsigned int Game::getNumAgents() const {
		unsigned int numAgents = 0;
		for (int i = 0; i < sizeof(__grid); ++i) {
			if (__grid[i]->getType() == STRATEGIC)
				numAgents++;
			if (__grid[i]->getType() == SIMPLE)
				numAgents++;
		}
		return numAgents;
	}

	unsigned int Game::getNumSimple() const {
		unsigned int numSimple = 0;
		for (int i = 0; i < sizeof(__grid); ++i) {
			if (__grid[i]->getType() == SIMPLE)
				numSimple++;
		}
		return numSimple;
	}

	unsigned int Game::getNumStrategic() const {
		unsigned int numStrategic = 0;
		for (int i = 0; i < sizeof(__grid); ++i) {
			if (__grid[i]->getType() == SIMPLE)
				numStrategic++;
		}
		return numStrategic;
	}

	unsigned int Game::getNumResources() {
		unsigned int numResources = 0;
		for (int i = 0; i < sizeof(__grid); ++i) {
			if (__grid[i]->getType() == FOOD)
				numResources++;
		}
		for (int i = 0; i < sizeof(__grid); ++i) {
			if (__grid[i]->getType() == ADVANTAGE)
				numResources++;
		}
		return numResources;
	}

	bool Game::addSimple(const Position &position) {
		Piece *P = new Simple(*this, position, STARTING_AGENT_ENERGY);
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addSimple(unsigned x, unsigned y) {
		Position position(x, y);
		Simple *P = new Simple(*this, position, STARTING_AGENT_ENERGY) ;
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addStrategic(const Position &position, Strategy *s) {
		Strategic * P = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
		Position position(x, y);
		Strategic * P = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addFood(const Position &position) {
		Food * P = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addFood(unsigned x, unsigned y) {
		Position position(x, y);
		Food * P = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
		///__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addAdvantage(const Position &position) {
		Advantage * P = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	bool Game::addAdvantage(unsigned x, unsigned y) {
		Position position(x, y);
		Advantage * P = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
		//__grid.push_back(P);
		//__grid.assign(position.x * __width + position.y, P);
		int loc;
		loc = (position.x * __width + position.y);
		__grid[loc] = P;
		return true;
	}

	const Surroundings Gaming::Game::getSurroundings() const {
		Surroundings Su;
		int num = 0, num1 = 0, w = 0;
		w = __width;
		Piece *P = *this->__grid.data();
		Position center;
		center = P->getPosition();
		num = (center.x * __width + center.y) - 4;
		/*
		for (int i = 0; i< __width; ++i) {
			for (int j = 0; j < __height; ++j) {
			int x, y;
				num1  = (num + (i  * w + j));
			if (num1 < 0) { }
			else {
				x = __grid[num1]->getPosition().x;
				y = __grid[num1]->getPosition().y;
				if (x > __width * __height || y > __width * __height) { }
				else {
					if (x == center.x - 1 && y == center.y - 1) {//0 (-1,-1)

						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x && y == center.y - 1) {//3 (0,-1)

						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x + 1 && y == center.y - 1) {//6 (1,-1)

						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x - 1 && y == center.y) {//1 (-1,0)

						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x && y == center.y) {//4 (0,-0)

						Su.array[i] = SELF;
					}
					if (x == center.x + 1 && y == center.y) {//7 (1,0)
						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x - 1 && y == center.y + 1) {//2 (-1,1)
						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x && y == center.y + 1) {//5 (0,1)
						Su.array[i] = __grid[num1]->getType();
					}
					if (x == center.x + 1 && y == center.y + 1) {//8 (1,1)
						Su.array[i] = __grid[num1]->getType();
					}
				}
			}
			*/
		for (int i = 0; i < __width; ++i) {
			for (int k = 0; k < __height; ++k) {
				int x, y;
				num1 = (num + (i * w + k));
				if (num1 < 0) {
					Su.array[(i * w + k)] = INACCESSIBLE;
				}
				else {
					if (__grid[num1] != nullptr) {
						if (num1 >= 0) {
							x = __grid[num1]->getPosition().x;
							y = __grid[num1]->getPosition().y;
							if (center.x < x - 1 || center.x > x + 1) {
								Su.array[(i * w + k)] = INACCESSIBLE;
							}
							if (center.y < y - 1 || center.y > y + 1) {
								Su.array[(i * w + k)] = INACCESSIBLE;
							}
							else if (__grid[num1]->isViable()) {
								Su.array[(i * w + k)] = __grid[num1]->getType();

							}
							else Su.array[(i * w + k)] = EMPTY;
						}
						if (__grid[num1] == nullptr) {
							Su.array[(i * w + k)] = EMPTY;
						}
					}
				}
		}
		}
		Su.array[4] = SELF;
		return Su;
	}

	const ActionType Gaming::Game::reachSurroundings(const Position &from, const Position &to) {
		if (from.x > to.x) { // N
			if (from.y == to.y)return N;
			if (from.y < to.y)return NW;
			if (from.y > to.y)return NE;
		}
		if (from.x == to.x) { // E or W
			if (from.y == to.y)return STAY;
			if (from.y < to.y)return W;
			if (from.y > to.y)return E;
		}
		if (from.x < to.x) { // S
			if (from.y == to.y)return S;
			if (from.y < to.y)return SW;
			if (from.y > to.y)return SE;
		}
		return STAY;
	}

	bool Game::isLegal(const ActionType &ac, const Position &pos) const {
		bool legal = true;

		auto Su = getSurroundings();
		switch (ac) {
		case N: {
			if (Su.array[1] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case NE: {
			if (Su.array[2] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case NW: {
			if (Su.array[0] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case E: {
			if (Su.array[5] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case W: {
			if (Su.array[3] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case SE: {
			if (Su.array[8] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case SW: {
			if (Su.array[6] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case S: {
			if (Su.array[7] == INACCESSIBLE) {
				legal = false;
			}break;
		}
		case STAY: {
			legal = true;
			break;
		}
		}

		return legal;
	}

	const Position Gaming::Game::move(const Position &pos, const ActionType &ac) const {
		Position posN;
		if (isLegal(ac, pos)) {
			unsigned int x = pos.x;
			unsigned int y = pos.y;

			switch (ac) {
			case N: posN.x = x - 1; break;
			case NE:posN.x = x - 1;posN.y = y + 1;break;
			case NW:posN.x = x - 1;posN.y = y - 1;break;
			case E:posN.y = y + 1;break;
			case W:posN.y = y - 1;break;
			case SE:posN.x = x + 1;posN.y = y + 1;break;
			case SW:posN.x = x + 1;posN.y = y - 1;break;
			case S:posN.x = x + 1;break;
			case STAY:posN = pos;break;
			}
			int tot, tot2;
			tot = (x*__width) + y;
			tot2 = (posN.x*__width) + posN.y;
			__grid.begin();
			if (__grid[tot]->getType() == FOOD) { posN = pos; }
			if (__grid[tot]->getType() == ADVANTAGE) { posN = pos; }
			if (__grid[tot2]->getType() == STRATEGIC) {
				__grid[tot]->interact((Agent *)__grid[tot2]);
			}
			if (__grid[tot2]->getType() == ADVANTAGE) {
				__grid[tot]->interact((Advantage *)__grid[tot2]);
			}
			if (__grid[tot2]->getType() == FOOD) {
				__grid[tot]->interact((Food *)__grid[tot2]);
			}
			if (!__grid[tot]->isViable()) { __grid[tot]->~Piece();__grid[tot]; }
			if (!__grid[tot2]->isViable()) { __grid[tot2]->~Piece();__grid[tot2]; }
		}

		return posN;
	}

	void Game::round() {
		for (auto j = 0; j < __grid.size(); ++j) {
			if (__grid[j] != 0) {
				if (__grid[j]->isViable()) {
					__grid[j]->~Piece();
				}
				if (!__grid[j]->getTurned()) {
					if (__grid[j]->getType() == STRATEGIC) {
						 __grid[j]->getPosition();
						__grid[j]->setPosition(move(__grid[j]->getPosition(),
							__grid[j]->takeTurn(getSurroundings())));
					}
				}
			}
		}
		for (auto j = 0; j < __grid.size(); ++j) {
			__grid[j]->age();
			__grid[j]->setTurned(false);
			if (__grid[j]->isViable()) {
				__grid[j]->~Piece();
				__grid[j] = 0;
			}
		}
	}

	void Game::populate() {
		if (!manual) {
			for (unsigned int j = 0; j < __height * __width; ++j) {
				__grid.push_back(nullptr);
			}
			unsigned int numStrategicP = __numInitAgents / 2;
			unsigned int numSimpleP = __numInitAgents - numStrategicP;
			unsigned int numAdvantagesP = __numInitResources / 4;
			unsigned int numFoodsP = __numInitResources - numAdvantagesP;
			std::default_random_engine gen;
			std::uniform_int_distribution<int> d(0, __width * __height);

			// populate Strategic agents
			while (numStrategicP > 0) {
				int i = d(gen); // random index in the grid vector
				if (__grid[i] == nullptr) { // is position empty
					Position pos(i / __width, i % __width);
					__grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
					numStrategicP--;
				}
			}

			// populate Simple agents
			while (numSimpleP > 0) {
				int i = d(gen); // random index in the grid vector
				if (__grid[i] == nullptr) { // is position empty
					Position pos(i / __width, i % __width);
					__grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
					numSimpleP--;
				}
			}

			// populate Food Resources
			while (numFoodsP > 0) {
				int i = d(gen); // random index in the grid vector
				if (__grid[i] == nullptr) { // is position empty
					Position pos(i / __width, i % __width);
					__grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
					numFoodsP--;
				}
			}
			// populate Advantage Reasorces
			while (numAdvantagesP > 0) {
				int i = d(gen); // random index in the grid vector
				if (__grid[i] == nullptr) { // is position empty
					Position pos(i / __width, i % __width);
					__grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
					numAdvantagesP--;
				}
			}
		}

	}
	void Game::play(bool verbose) {
		if (verbose){
			populate();



		}

	}

}