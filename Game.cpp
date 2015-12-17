//
// Created by Travis Milton on 12/10/15.
//

#include "Game.h"
#include "Piece.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"
#include "Exceptions.h"


namespace Gaming {
	const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

	Gaming::PositionRandomizer Game::__posRandomizer;

	const unsigned Game::MIN_WIDTH = 3;
	const unsigned Game::MIN_HEIGHT = 3;
	const double Game::STARTING_AGENT_ENERGY = 20;
	const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game() : __width(MIN_WIDTH), __height(MIN_HEIGHT) {
        for (int i = 0; i < (__width * __height); i++) {
            __grid.push_back(nullptr);
        }
        //__grid.resize(__width * __height);


	}

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height),
                                                               __numInitAgents(NUM_INIT_AGENT_FACTOR),
                                                               __numInitResources(NUM_INIT_RESOURCE_FACTOR) {
        if (width > 2) {
            __width = width;
        }
        else;//throw InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,width,height);
        if (height > 2) {
            __height = height;
        }
        else;//throw InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,width,height);
        for (int i = 0; i < (__width * __height); i++) {
            __grid.push_back(nullptr);
        }
        if (!manual) { void populate(); }

	}

	Game::Game(const Game &another) {
        __grid = another.__grid;
        __height = another.__height;
        __width = another.__width;
        __round = another.__round;
    }
	Game::~Game() {

	}

	unsigned int Game::getNumPieces() const {
        auto it = __grid.begin();
        unsigned int count = 0;
        for (; it != __grid.end(); ++it) {
            if (*it != nullptr) {
                if ((*it)->getType() == SIMPLE) { count++; }
                if ((*it)->getType() == STRATEGIC) { count++; }
                if ((*it)->getType() == ADVANTAGE) { count++; }
                if ((*it)->getType() == FOOD) { count++; }
            }
        }
        return count;
    }

    unsigned int Game::getNumAgents() const { return getNumSimple() + getNumStrategic(); }


	unsigned int Game::getNumSimple() const {
        auto it = __grid.begin();
        unsigned int count = 0;
        for (; it != __grid.end(); ++it) {
            if (*it != nullptr) {
                if ((*it)->getType() == SIMPLE) { count++; }
            }
        }
        return count;
    }

	unsigned int Game::getNumStrategic() const {
        auto it = __grid.begin();
        unsigned int count = 0;
        for (; it != __grid.end(); ++it) {
            if (*it != nullptr) {
                if ((*it)->getType() == STRATEGIC) { count++; }
            }
        }
        return count;
    }

	unsigned int Game::getNumResources() {
        auto it = __grid.begin();
        unsigned int count = 0;
        for (; it != __grid.end(); ++it) {
            if (*it != nullptr) {
                if ((*it)->getType() == ADVANTAGE) { count++; }
                if ((*it)->getType() == FOOD) { count++; }
            }
        }
        return count;
    }

	bool Game::addSimple(const Position &position) {
        unsigned int x = position.x;
        unsigned int y = position.y;
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Simple(*this, position, STARTING_AGENT_ENERGY);
        return true;
	}

	bool Game::addSimple(unsigned x, unsigned y) {
		Position position(x, y);
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Simple(*this, position, STARTING_AGENT_ENERGY);
        return true;
	}

	bool Game::addStrategic(const Position &position, Strategy *s) {
        unsigned int x = position.x;
        unsigned int y = position.y;
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
        return true;
	}

	bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
		Position position(x, y);
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
        return true;
	}

	bool Game::addFood(const Position &position) {
        unsigned int x = position.x;
        unsigned int y = position.y;
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
        return true;
	}

	bool Game::addFood(unsigned x, unsigned y) {
		Position position(x, y);
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
        return true;
	}

	bool Game::addAdvantage(const Position &position) {
        unsigned int x = position.x;
        unsigned int y = position.y;
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
        return true;
	}

	bool Game::addAdvantage(unsigned x, unsigned y) {
		Position position(x, y);
        if (__grid[x * __width + y] != nullptr) { return false; }
        __grid[x * __width + y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
        return true;
	}

    const Surroundings Gaming::Game::getSurroundings(Position const &p) const {
        Surroundings s;
        int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, q, r, t;
        a = p.x - 1;
        b = p.y - 1;
        if (a < 0 || b < 0 || a > (__height - 1) || b > (__width - 1)) {
            s.array[0] = INACCESSIBLE;
        }
        else if (__grid[a * __width + b] == nullptr) { s.array[0] = EMPTY; }
        else { s.array[0] = __grid[a * __width + b]->getType(); }
        c = p.x - 1;
        d = p.y;
        if (c < 0 || d < 0 || c > (__height - 1) || d > (__width - 1)) { s.array[1] = INACCESSIBLE; }
        else if (__grid[c * __width + d] == nullptr) { s.array[1] = EMPTY; }
        else { s.array[1] = __grid[c * __width + d]->getType(); }
        e = p.x - 1;
        f = p.y + 1;
        if (e < 0 || f < 0 || e > (__height - 1) || f > (__width - 1)) { s.array[2] = INACCESSIBLE; }
        else if (__grid[e * __width + f] == nullptr) { s.array[2] = EMPTY; }
        else { s.array[2] = __grid[e * __width + f]->getType(); }
        g = p.x;
        h = p.y - 1;
        if (g < 0 || h < 0 || g > (__height - 1) || h > (__width - 1)) { s.array[3] = INACCESSIBLE; }
        else if (__grid[g * __width + h] == nullptr) { s.array[3] = EMPTY; }
        else { s.array[3] = __grid[g * __width + h]->getType(); }
        i = p.x;
        j = p.y;
        if (i < 0 || j < 0 || i > (__height - 1) || j > (__width - 1)) { s.array[4] = INACCESSIBLE; }
        else if (__grid[i * __width + j] == nullptr) { s.array[4] = EMPTY; }
        else { s.array[4] = SELF; }
        k = p.x;
        l = p.y + 1;
        if (k < 0 || l < 0 || k > (__height - 1) || l > (__width - 1)) { s.array[5] = INACCESSIBLE; }
        else if (__grid[k * __width + l] == nullptr) { s.array[5] = EMPTY; }
        else { s.array[5] = __grid[k * __width + l]->getType(); }
        m = p.x + 1;
        n = p.y - 1;
        if (m < 0 || n < 0 || m > (__height - 1) || n > (__width - 1)) { s.array[6] = INACCESSIBLE; }
        else if (__grid[m * __width + n] == nullptr) { s.array[6] = EMPTY; }
        else { s.array[6] = __grid[m * __width + n]->getType(); }
        o = p.x + 1;
        q = p.y;
        if (o < 0 || q < 0 || o > (__height - 1) || q > (__width - 1)) { s.array[7] = INACCESSIBLE; }
        else if (__grid[o * __width + q] == nullptr) { s.array[7] = EMPTY; }
        else { s.array[7] = __grid[o * __width + q]->getType(); }
        r = p.x + 1;
        t = p.y + 1;
        if (r < 0 || t < 0 || r > (__height - 1) || t > (__width - 1)) { s.array[8] = INACCESSIBLE; }
        else if (__grid[r * __width + t] == nullptr) { s.array[8] = EMPTY; }
        else { s.array[8] = __grid[r * __width + t]->getType(); }
        return s;
	}

	const ActionType Gaming::Game::reachSurroundings(const Position &from, const Position &to) {
        if ((from.x - to.x) == 1 && (from.y - to.y) == 0) { return N; }
        if ((from.x - to.x) == 1 && (from.y - to.y) == -1) { return NE; }
        if ((from.x - to.x) == 0 && (from.y - to.y) == -1) { return E; }
        if ((from.x - to.x) == -1 && (from.y - to.y) == -1) { return SE; }
        if ((from.x - to.x) == -1 && (from.y - to.y) == 0) { return S; }
        if ((from.x - to.x) == -1 && (from.y - to.y) == 1) { return SW; }
        if ((from.x - to.x) == 0 && (from.y - to.y) == 1) { return W; }
        if ((from.x - to.x) == 1 && (from.y - to.y == 1)) { return NW; }
        else
            return STAY;
	}

	bool Game::isLegal(const ActionType &ac, const Position &pos) const {
		bool legal = true;
        auto Su = getSurroundings(pos);
		switch (ac) {
            case N: {
                if (Su.array[1] == INACCESSIBLE) {
                    legal = false;
                    break;
                }
            }
            case NE: {
                if (Su.array[2] == INACCESSIBLE) { break; }
            }
            case NW: {
                if (Su.array[0] == INACCESSIBLE) {
                    legal = false;
                    break;
                }
            }
            case E: {
                if (Su.array[5] == INACCESSIBLE) { break; }
            }
            case W: {
                if (Su.array[3] == INACCESSIBLE) {
                    legal = false;
                    break;
                }
            }
            case SE: {
                if (Su.array[8] == INACCESSIBLE) {
                    legal = false;
                    break;
                }
            }
            case SW: {
                if (Su.array[6] == INACCESSIBLE) {
                    legal = false;
                    break;
                }
            }
            case S: {
                if (Su.array[7] == INACCESSIBLE) {
                    legal = false;
                    break;
                }
            }
            case STAY: {
                legal = true;
                break;
            }
        }
        return legal;
    }



	const Position Gaming::Game::move(const Position &pos, const ActionType &ac) const {
        Position new_pos;
        if (isLegal(ac, pos) == true) {
            if (ac == N) {
                new_pos.x = pos.x - 1;
                new_pos.y = pos.y;
                return new_pos;
            }
            if (ac == NW) {
                new_pos.x = pos.x - 1;
                new_pos.y = pos.y - 1;
                return new_pos;
            }
            if (ac == NE) {
                new_pos.x = pos.x - 1;
                new_pos.y = pos.y + 1;
                return new_pos;
            }
            if (ac == S) {
                new_pos.x = pos.x + 1;
                new_pos.y = pos.y;
                return new_pos;
            }
            if (ac == SW) {
                new_pos.x = pos.x + 1;
                new_pos.y = pos.y - 1;
                return new_pos;
            }
            if (ac == SE) {
                new_pos.x = pos.x + 1;
                new_pos.y = pos.y + 1;
                return new_pos;
            }
            if (ac == E) {
                new_pos.x = pos.x;
                new_pos.y = pos.y + 1;
                return new_pos;
            }
            if (ac == W) {
                new_pos.x = pos.x;
                new_pos.y = pos.y - 1;
                return new_pos;
            }
        }
        return pos;
    }

	void Game::round() {
        auto it = __grid.begin();
        for (; it != __grid.end(); ++it) {
            if (*it != nullptr) {
                if (!(*it)->getTurned()) {
                    (*it)->takeTurn(getSurroundings((*it)->getPosition()));
                    (*it)->setTurned(true);
                }
            }
        }
        it = __grid.begin();
        for (; it != __grid.end(); ++it) {
            if (*it != nullptr) {
                if ((*it)->isViable()) {
                    (*it)->age();
                    (*it)->setTurned(false);
                }
            }
        }

	}

	void Game::populate() {
		if (!manual) {

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
            round();

		}

	}

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Round " << game.getRound() << ":" << std::endl;
        for (int j = 0; j < game.__height; j++) {
            for (int k = 0; k < game.__width; k++) {
                if (game.__grid[k] != nullptr) {
                    os << "[" << *game.__grid[k] << "     ]";
                } else {
                    os << "[     ]";
                }
            }
            os << std::endl;
        }
        if (game.getStatus() == 0)
            os << "Status: Not Started" << std::endl;
        else if (game.getStatus() == 1)
            os << "Status: Playing..." << std::endl;
        else
            os << "Status: Over!" << std::endl;
        return os;
    };

}