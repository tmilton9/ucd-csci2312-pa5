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
#include <set>

namespace Gaming {
	const unsigned int Game::NUM_INIT_AGENT_FACTOR    = 4;  // factor for auto pop of agents
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;  // factor for auto pop or resources

	Gaming::PositionRandomizer Game::__posRandomizer;       // used to provide a random position during turns

	const unsigned Game::MIN_WIDTH                  = 3;    // min game board height
	const unsigned Game::MIN_HEIGHT                 = 3;    // min game board width
	const double   Game::STARTING_AGENT_ENERGY      = 20;   // default starting agent energy
	const double   Game::STARTING_RESOURCE_CAPACITY = 10;   // default starting resource cap

	//**********************************************************************
	// Method:    Game
	// FullName:  Gaming::Game::Game
	// Access:    public
	// Returns:
	// Qualifier:
	// Info:      this sets all defaults and assumes automatic population
	//**********************************************************************
	Game::Game() {
		__width            = 3;
		__height           = 3;
		__numInitAgents    = 0;
		__numInitResources = 0;
		__round            = 0;
		std::vector<Piece *> temp(__width * __height, nullptr);
		__grid   = temp;
		__status = PLAYING;
	}

	//**********************************************************************
	// Method:    Game
	// FullName:  Gaming::Game::Game
	// Access:    public
	// Returns:
	// Qualifier:
	// Parameter: unsigned width
	// Parameter: unsigned height
	// Parameter: bool manual
	// Info:      constructor for manual size declaration
	//            and user defined manual or auto pop
	//**********************************************************************
	Game::Game(unsigned width, unsigned height, bool manual) {
		if (width < MIN_WIDTH || height < MIN_HEIGHT) {
			throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
		}
		__width  = width;
		__height = height;
		if (manual) {
			__numInitAgents    = (__width * __height) / NUM_INIT_AGENT_FACTOR;
			__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
		}
		else {
			__numInitResources = 0;
			__numInitAgents    = 0;
		}
		__round  = 0;
		std::vector<Piece *> temp(__width * __height, nullptr);
		__grid = temp;
		if (manual) { populate(); }
	}

	//**********************************************************************
	// Method:    Game
	// FullName:  Gaming::Game::Game
	// Access:    public
	// Returns:
	// Qualifier:
	// Parameter: const Game & another
	// Info:      constructor call to copy one game to another
	//            used for __game in Piece
	//**********************************************************************
	Game::Game(const Game &another) {
		__grid             = another.__grid;
		__height           = another.__height;
		__width            = another.__width;
		__round            = another.__round;
		__status           = another.__status;
		__numInitAgents    = another.__numInitAgents;
		__numInitResources = another.__numInitAgents;
		__verbose          = another.__verbose;
	}

	//**********************************************************************
	// Method:    ~Game
	// FullName:  Gaming::Game::~Game
	// Access:    public
	// Returns:
	// Qualifier:
	// Info:      destructor
	//**********************************************************************
	Game::~Game() {
	}

	//**********************************************************************
	// Method:    operator<<
	// FullName:  Gaming::operator<<
	// Access:    public
	// Returns:   std::ostream &
	// Qualifier:
	// Parameter: std::ostream & os
	// Parameter: const Game & game
	// Info:      base print call overload calls individual Piece to
	//            print themselves and formats output
	//**********************************************************************
	std::ostream &operator<<(std::ostream &os, const Game &game) {
		os << "Round " << game.getRound() << ":" << std::endl;// prints round number
		for (int j = 0; j < game.__height; j++) {             // loop rows
			for (int k = 0; k < game.__width; k++) {          // loop cols
				if (game.__grid[k] != nullptr) {              // if position is not 0
					os << "[" << *game.__grid[k] << "]";      // print position information
				}
				else {                                        // if position is 0
					os << "[     ]";                          // print blank space
				}
			}
			os << std::endl;                                  // end the line after both loops
		}
		if (game.getStatus() == 0) {                          // output statements for status
			os << "Status: Not Started" << std::endl;
		} else if (game.getStatus() == 1) {
			os << "Status: Playing..." << std::endl;
		} else {
			os << "Status: Over!" << std::endl;
		}
		return os;
	};

	//**********************************************************************
	// Method:    getNumPieces
	// FullName:  Gaming::Game::getNumPieces
	// Access:    public
	// Returns:   unsigned int
	// Qualifier: const
	// Info:      function to determine number of remaining Pieces on board
	//**********************************************************************
	unsigned int Game::getNumPieces() const {
		auto         it    = __grid.begin();                   // iterator
		unsigned int count = 0;                                // return value
		for (; it != __grid.end(); ++it) {                     // loop grid
			if (*it != nullptr) {                              // if not 0
				if ((*it)->getType() == SIMPLE) { count++; }   // check the Type and
				if ((*it)->getType() == STRATEGIC) { count++; }// if valid count +1
				if ((*it)->getType() == ADVANTAGE) { count++; }
				if ((*it)->getType() == FOOD) { count++; }
			}
		}
		return count;
	}

	//*********************************************************************
	// Method:    getNumAgents
	// FullName:  Gaming::Game::getNumAgents
	// Access:    public
	// Returns:   unsigned int
	// Qualifier: const
	// Info:      function to determine number of agents on board
	//            calls getNumSimple and getNumStrategic
	//*********************************************************************
	unsigned int Game::getNumAgents() const {               // calls functions to count Simple and Strategic
		return getNumSimple() + getNumStrategic();
	}

	//*********************************************************************
	// Method:    getNumSimple
	// FullName:  Gaming::Game::getNumSimple
	// Access:    public
	// Returns:   unsigned int
	// Qualifier: const
	// Info:      function to determine number of Simple Agents on board
	//*********************************************************************
	unsigned int Game::getNumSimple() const {
		auto         it    = __grid.begin();                // iterator
		unsigned int count = 0;                             // iterator
		for (; it != __grid.end(); ++it) {                  // loop grid
			if (*it != nullptr) {                           // if not 0
				if ((*it)->getType() == SIMPLE) { count++; }// if Simple increment count
			}
		}
		return count;
	}

	//*********************************************************************
	// Method:    getNumStrategic
	// FullName:  Gaming::Game::getNumStrategic
	// Access:    public
	// Returns:   unsigned int
	// Qualifier: const
	// Info:      function to determine number of Strategic Agents on board
	//*********************************************************************
	unsigned int Game::getNumStrategic() const {
		auto         it    = __grid.begin();                    // iterator
		unsigned int count = 0;                                 // iterator
		for (; it != __grid.end(); ++it) {                      // loop grid
			if (*it != nullptr) {                               // if not 0
				if ((*it)->getType() == STRATEGIC) { count++; } // if Strategic increment count
			}
		}
		return count;
	}

	//*********************************************************************
	// Method:    getNumResources
	// FullName:  Gaming::Game::getNumResources
	// Access:    public
	// Returns:   unsigned int
	// Qualifier:
	// Info:      function to determine number of Food and Advantage
	//            Resources on board
	//*********************************************************************
	unsigned int Game::getNumResources() {
		auto         it    = __grid.begin();                    // iterator
		unsigned int count = 0;                                 // iterator
		for (; it != __grid.end(); ++it) {                      // loop grid
			if (*it != nullptr) {                               // if not 0
				if ((*it)->getType() == ADVANTAGE) { count++; } // if Advantage increment count
				if ((*it)->getType() == FOOD) { count++; }      // if Food increment count
			}
		}
		return count;
	}

	//*********************************************************************
	// Method:    addSimple
	// FullName:  Gaming::Game::addSimple
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: const Position & position
	// Info:      adds a Simple Agent to a specific Position on board
	//*********************************************************************
	bool Game::addSimple(const Position &position) {
		unsigned int x = position.x;                             // sets x from pos info
		unsigned int y = position.y;                             // sets y from pos info
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Simple(*this, position, STARTING_AGENT_ENERGY);
		return true;
	}

	//*********************************************************************
	// Method:    addSimple
	// FullName:  Gaming::Game::addSimple
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: unsigned x
	// Parameter: unsigned y
	// Info:      adds a Simple Agent using x and y coordanents to board
	//*********************************************************************
	bool Game::addSimple(unsigned x, unsigned y) {
		Position position(x, y);
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
															     // create new Piece for position
		__grid[x * __width + y] = new Simple(*this, position, STARTING_AGENT_ENERGY);
		return true;
	}

	//*********************************************************************
	// Method:    addStrategic
	// FullName:  Gaming::Game::addStrategic
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: const Position & position
	// Parameter: Strategy * s
	// Info:      adds a Strategic Agent to a specific Position on board
	//*********************************************************************
	bool Game::addStrategic(const Position &position, Strategy *s) {
		unsigned int x = position.x;                             // sets x from pos info
		unsigned int y = position.y;                             // sets y from pos info
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
		return true;
	}

	//*********************************************************************
	// Method:    addStrategic
	// FullName:  Gaming::Game::addStrategic
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: unsigned x
	// Parameter: unsigned y
	// Parameter: Strategy * s
	// Info:      adds a Strategic Agent using x and y coordanents to board
	//*********************************************************************
	bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
		Position position(x, y);
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
		return true;
	}

	//*********************************************************************
	// Method:    addFood
	// FullName:  Gaming::Game::addFood
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: const Position & position
	// Info:      adds a Food Resource to a specific Position on board
	//*********************************************************************
	bool Game::addFood(const Position &position) {
		unsigned int x = position.x;                             // sets x from pos info
		unsigned int y = position.y;                             // sets y from pos info
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
		return true;
	}

	//*********************************************************************
	// Method:    addFood
	// FullName:  Gaming::Game::addFood
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: unsigned x
	// Parameter: unsigned y
	// Info:      adds a Food Resource using x and y coordanents to board
	//*********************************************************************
	bool Game::addFood(unsigned x, unsigned y) {
		Position position(x, y);
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
		return true;
	}

	//*********************************************************************
	// Method:    addAdvantage
	// FullName:  Gaming::Game::addAdvantage
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: const Position & position
	// Info:      adds a Advantage Resource to a specific Position on board
	//*********************************************************************
	bool Game::addAdvantage(const Position &position) {
		unsigned int x = position.x;                             // sets x from pos info
		unsigned int y = position.y;                             // sets y from pos info
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
		return true;
	}

	//*********************************************************************
	// Method:    addAdvantage
	// FullName:  Gaming::Game::addAdvantage
	// Access:    public
	// Returns:   bool
	// Qualifier:
	// Parameter: unsigned x
	// Parameter: unsigned y
	// Info:      adds a Advantage Resource using x and y coordanents to board
	//*********************************************************************
	bool Game::addAdvantage(unsigned x, unsigned y) {
		Position position(x, y);
		if (x >= __height || y >= __width) {                     // check for out of bounds
			throw OutOfBoundsEx(__width, __height, x, y); }      // throw exception if out of bounds
		if (__grid[x * __width + y] != nullptr) { return false; }// if position is taken return false
																 // create new Piece for position
		__grid[x * __width + y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
		return true;
	}

	//*********************************************************************
	// Method:    getSurroundings
	// FullName:  Gaming::Game::getSurroundings
	// Access:    public
	// Returns:   const Surroundings
	// Qualifier: const
	// Parameter: Position const & p
	// Info:      function returns the surroundings of the Position that is
	//            passed to it and returns an Surroundings array to calling
	//            function the array is formatted: 0-8
	//                        NW, N, NE, W, SELF, E, SW, S, SE
	//*********************************************************************
	const Surroundings Gaming::Game::getSurroundings(Position const &p) const {
		Surroundings                s;                            // array object to be returned
		int                         a, b,                         // x, y pos 0
		                            c, d,                         // x, y pos 1
		                            e, f,                         // x, y pos 2
		                            g, h,                         // x, y pos 3
		                            i, j,                         // x, y pos 4
		                            k, l,                         // x, y pos 5
		                            m, n,                         // x, y pos 6
		                            o, q,                         // x, y pos 7
		                            r, t;                         // x, y pos 8
																  // sets for NW
		a = p.x - 1;
		b = p.y - 1;

		if (a < 0 || b < 0 || a > (__height - 1) || b > (__width - 1)) {
			s.array[0] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[a * __width + b] == nullptr) {
			s.array[0] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[0] = __grid[a * __width + b]->getType(); } // set Piece type in the array
																  // sets for N
		c = p.x - 1;
		d = p.y;

		if (c < 0 || d < 0 || c > (__height - 1) || d > (__width - 1)) {
			s.array[1] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[c * __width + d] == nullptr) {
			s.array[1] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[1] = __grid[c * __width + d]->getType(); } // set Piece type in the array
																  // sets for NE
		e = p.x - 1;
		f = p.y + 1;

		if (e < 0 || f < 0 || e > (__height - 1) || f > (__width - 1)) {
			s.array[2] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[e * __width + f] == nullptr) {
			s.array[2] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[2] = __grid[e * __width + f]->getType(); } // set Piece type in the array
																  // sets for W
		g = p.x;
		h = p.y - 1;

		if (g < 0 || h < 0 || g > (__height - 1) || h > (__width - 1)) {
			s.array[3] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[g * __width + h] == nullptr) {
			s.array[3] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[3] = __grid[g * __width + h]->getType(); } // set Piece type in the array
																  // sets for self
		i = p.x;
		j = p.y;

		if (i < 0 || j < 0 || i > (__height - 1) || j > (__width - 1)) {
			s.array[4] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[i * __width + j] == nullptr) {
			s.array[4] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[4] = SELF; }                               // set Piece type in the array
																  // sets for E
		k = p.x;
		l = p.y + 1;

		if (k < 0 || l < 0 || k > (__height - 1) || l > (__width - 1)) {
			s.array[5] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[k * __width + l] == nullptr) {
			s.array[5] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[5] = __grid[k * __width + l]->getType(); } // set Piece type in the array
																  // sets for SW
		m = p.x + 1;
		n = p.y - 1;

		if (m < 0 || n < 0 || m > (__height - 1) || n > (__width - 1)) {
			s.array[6] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[m * __width + n] == nullptr) {
			s.array[6] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[6] = __grid[m * __width + n]->getType(); } // set Piece type in the array
																  // sets for S
		o = p.x + 1;
		q = p.y;

		if (o < 0 || q < 0 || o > (__height - 1) || q > (__width - 1)) {
			s.array[7] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[o * __width + q] == nullptr) {
			s.array[7] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[7] = __grid[o * __width + q]->getType(); } // set Piece type in the array
																  // sets for SE
		r = p.x + 1;
		t = p.y + 1;

		if (r < 0 || t < 0 || r > (__height - 1) || t > (__width - 1)) {
			s.array[8] = INACCESSIBLE; }                          // if not on the board if !is then mark Inaccessible
		else if (__grid[r * __width + t] == nullptr) {
			s.array[8] = EMPTY; }                                 // if the valid location is empty mark Empty
		else { s.array[8] = __grid[r * __width + t]->getType(); } // set Piece type in the array

		return s;
	}

	//*********************************************************************
	// Method:    reachSurroundings
	// FullName:  Gaming::Game::reachSurroundings
	// Access:    public static
	// Returns:   const ActionType
	// Qualifier:
	// Parameter: const Position & from
	// Parameter: const Position & to
	// Info:      functon that takes an input of two Positions and returns
	//            the Action type required to reach the to location
	//*********************************************************************
	const ActionType Gaming::Game::reachSurroundings(const Position &from, const Position &to) {
		if ((from.x - to.x) == 1 && (from.y - to.y) == 0) { return N; }
		if ((from.x - to.x) == 1 && (from.y - to.y) == -1) { return NE; }
		if ((from.x - to.x) == 0 && (from.y - to.y) == -1) { return E; }
		if ((from.x - to.x) == -1 && (from.y - to.y) == -1) { return SE; }
		if ((from.x - to.x) == -1 && (from.y - to.y) == 0) { return S; }
		if ((from.x - to.x) == -1 && (from.y - to.y) == 1) { return SW; }
		if ((from.x - to.x) == 0 && (from.y - to.y) == 1) { return W; }
		if ((from.x - to.x) == 1 && (from.y - to.y) == 1) { return NW; }
		else {
			return STAY;
		}
	}

	//*********************************************************************
	// Method:    isLegal
	// FullName:  Gaming::Game::isLegal
	// Access:    public
	// Returns:   bool
	// Qualifier: const
	// Parameter: const ActionType & ac
	// Parameter: const Position & pos
	// Info:      function is called to detirmine if requested Action type
	//            is a valid move
	//*********************************************************************
	bool Game::isLegal(const ActionType &ac, const Position &pos) const {
		bool legal = true;                              // return item
		auto Su    = getSurroundings(pos);              // surroundings array

		switch (ac) {                                   // Switch to check values of ac

			case N: {                                   // checks if N is valid
				if (Su.array[1] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case NE: {                                  // checks if NE is valid
				if (Su.array[2] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case NW: {                                  // checks if NW is valid
				if (Su.array[0] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case E: {                                   // checks if E is valid
				if (Su.array[5] == INACCESSIBLE) {
					legal = false;
					break; }
				else { return true; }
			}
			case W: {                                   // checks if W is valid
				if (Su.array[3] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case SE: {                                  // checks if SE is valid
				if (Su.array[8] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case SW: {                                  // checks if SW is valid
				if (Su.array[6] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case S: {                                   // checks if S is valid
				if (Su.array[7] == INACCESSIBLE) {
					legal = false; break; }
				else { return true; }
			}
			case STAY: {
				legal = true; break; }                  // if ac is Stay return true
		}
		return legal;                                   // used to remove warnings on compiler
														// process should never reach here unless
														// data is corrupt
	}

	//*********************************************************************
	// Method:    move
	// FullName:  Gaming::Game::move
	// Access:    public
	// Returns:   const Position
	// Qualifier: const
	// Parameter: const Position & pos
	// Parameter: const ActionType & ac
	// Info:      function that performs the actual movement of Agents on
	//            the board and initiates interactions between Pieces
	//*********************************************************************
	const Position Gaming::Game::move(const Position &pos, const ActionType &ac) const {
		Position new_pos;                                   // return value

		if (isLegal(ac, pos)) {                             // calls isLegal to prevent movement errors
			if (ac == N) {                                  // processes N
				new_pos.x = pos.x - 1;                      // set new pos values
				new_pos.y = pos.y;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == NW) {                                 // processes NW
				new_pos.x = pos.x - 1;                      // set new pos values
				new_pos.y = pos.y - 1;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == NE) {                                 // processes NE
				new_pos.x = pos.x - 1;                      // set new pos values
				new_pos.y = pos.y + 1;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == S) {                                  // processes S
				new_pos.x = pos.x + 1;                      // set new pos values
				new_pos.y = pos.y;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == SW) {                                 // processes SW
				new_pos.x = pos.x + 1;                      // set new pos values
				new_pos.y = pos.y - 1;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == SE) {                                 // processes SE
				new_pos.x = pos.x + 1;                      // set new pos values
				new_pos.y = pos.y + 1;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == E) {                                  // processes E
				new_pos.x = pos.x;                          // set new pos values
				new_pos.y = pos.y + 1;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
			if (ac == W) {                                  // processes W
				new_pos.x = pos.x;                          // set new pos values
				new_pos.y = pos.y - 1;
				if (__grid[new_pos.x * __width + new_pos.y] != 0) {
															// check for empty if ! then perform
															// Piece interaction
					this->__grid[pos.x * __width + pos.y]->operator*(*__grid[new_pos.x * __width + new_pos.y]);
				}
				return new_pos;                             // return new location
			}
		}
		return pos;
	}

	//*********************************************************************
	// Method:    round
	// FullName:  Gaming::Game::round
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Info:      function to control the game play and turn taking by the
	//            Agents. Sets the new position of Agents that have moved
	//            checks if Pieces are viable and removes if nessasary
	//            increments round counter
	//*********************************************************************
	void Game::round() {

		for (int i = 0; i < __width * __height; i++) {      // loops the game through
															// all positions
			if (__grid[i] != nullptr && !(__grid[i]->isViable())) {
				delete __grid[i];
				__grid[i] = nullptr;                        // if the Piece is not valid delete
			}
			if (__grid[i] != nullptr){
				if (__grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE){__grid[i]->setTurned(true);}
				else if (!(__grid[i]->getTurned())) {
															// if the Piece in the position
															// has not had a turn then call setPosition
				__grid[i]->setPosition(
						move(__grid[i]->getPosition(), __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()))));
															// setPosition calls move with the current
															// position and a takeTurn call takeTurn calls
															// getSurroundings with the current position
				if (__grid[i]->isViable()) {                // if this statement is removed tests wont complete
					Position newPos = __grid[i]->getPosition();
					__grid[newPos.x * __width + newPos.y] = __grid[i];
					__grid[i]                             = nullptr;
					}
				}
			}
		}
		for (int i = 0; i < __width * __height; i++) {      // runs through the positons to check for viable
			if (__grid[i] != nullptr) {                     // if not 0
				if (__grid[i]->isViable()) {                // check for viable
					__grid[i]->age();                       // age position
					__grid[i]->setTurned(false); }          // set to not turned
				if (!(__grid[i]->isViable())) {             // if Peice is not viable delete
					delete __grid[i];
					__grid[i] = nullptr;
				}
			}
		}
		__round++;
	}

	//*********************************************************************
	// Method:    populate
	// FullName:  Gaming::Game::populate
	// Access:    private
	// Returns:   void
	// Qualifier:
	// Info:      function populates the game board when the game is set
	//            to manual false
	//*********************************************************************
	void Game::populate() {
		if (!manual) {                                      // checks the manual flag
			// works through the preset values to
			// detirmine the initial Pieces
			unsigned int numStrategicP = __numInitAgents / 2;
			unsigned int numSimpleP = __numInitAgents - numStrategicP;
			unsigned int numAdvantagesP = __numInitResources / 4;
			unsigned int numFoodsP = __numInitResources - numAdvantagesP;

			std::default_random_engine         gen;         // random generator
			std::uniform_int_distribution<int> d(0, __width * __height);

			while (numStrategicP > 0) {                     // loop to initialize Strategic Agents
				int i = d(gen);                             // random grid position
				if (__grid[i] == nullptr) {                 // is position empty
					Position pos(i / __width, i % __width); // create Piece
					__grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
					numStrategicP--;                        // subtract from the number needed
				}
			}

			while (numSimpleP > 0) {                        // loop to initialize Simple Agents
				int i = d(gen);                             // random grid position
				if (__grid[i] == nullptr) {                 // is position empty
					Position pos(i / __width, i % __width); // create Piece
					__grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
					numSimpleP--;                           // subtract from the number needed
				}
			}

			while (numFoodsP > 0) {                         // loop to initialize Food Resources
				int i = d(gen);                             // random grid position
				if (__grid[i] == nullptr) {                 // is position empty
					Position pos(i / __width, i % __width); // create Piece
					__grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
					numFoodsP--;                            // subtract from the number needed
				}
			}

			while (numAdvantagesP > 0) {                    // loop to initialize Advantage Resorces
				int i = d(gen);                             // random grid position
				if (__grid[i] == nullptr) {                 // is position empty
					Position pos(i / __width, i % __width); // create Piece
					__grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
					numAdvantagesP--;                       // subtract from the number needed
				}
			}
		}
	}

	//*********************************************************************
	// Method:    play
	// FullName:  Gaming::Game::play
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Parameter: bool verbose
	// Info:      function starts the game and determines if the game
	//            turns are printed or just the results
	//*********************************************************************
	void Game::play(bool verbose) {
		__status = PLAYING;                                 // sets the status to playing
		while (__status != OVER) {                          // runs until the status is set to over
			if (verbose) {                                  // if verbose is true
				std::cout << *this;
			}                                               // prints out the game board
			round();                                        // calls the round function to play the game
			if (getNumResources() == 0) {                   // checks if the game is over
				__status = OVER;
			}                                               // ends game
		}
		if (verbose) {                                      // if verbose is true
			std::cout << *this;
		}                                                   // prints out the game board
	}
}