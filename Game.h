//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_GAME_H
#define PA5GAME_GAME_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <regex>
#include <sstream>

#include "Gaming.h"
#include "DefaultAgentStrategy.h"

namespace Gaming {

    class Piece;
    class Agent;
    class Strategy;
    class DefaultAgentStrategy;

    class Game {
    public:
        enum Status { NOT_STARTED, PLAYING, OVER };

    private:
        static const unsigned int NUM_INIT_AGENT_FACTOR;
        static const unsigned int NUM_INIT_RESOURCE_FACTOR;

        static PositionRandomizer __posRandomizer;

        void populate(); // populate the grid (used in automatic random initialization of a Game)

        unsigned __numInitAgents, __numInitResources;
        unsigned int numPositions = 0;
        unsigned int numStrategic = 0;
        unsigned int numSimple = 0;
        unsigned int numAdvantages = 0;
        unsigned int numFoods = 0;
        unsigned __width, __height;
        std::vector<Piece *> __grid; // if a position is empty, nullptr

        unsigned int __round;

        Status __status;
        bool manual;
        bool __verbose;

    public:
        static const unsigned MIN_WIDTH, MIN_HEIGHT;
        static const double STARTING_AGENT_ENERGY;
        static const double STARTING_RESOURCE_CAPACITY;

        Game();
        Game(unsigned width, unsigned height, bool manual1); // note: manual population by default
        Game(const Game &another);
        Game &operator=(const Game &other) = delete;
        ~Game();

        // getters
        unsigned int getWidth() const { return __width; }
        unsigned int getHeight() const { return __height; }
        unsigned int getNumPieces() const;
        unsigned int getNumAgents() const;
        unsigned int getNumSimple() const;
        unsigned int getNumStrategic() const;
        unsigned int getNumResources();
        Status getStatus() const { return __status; }
        unsigned int getRound() const { return __round; }

        // grid population methods
        bool addSimple(const Position &position);
        bool addSimple(unsigned x, unsigned y);
        bool addStrategic(const Position &position, Strategy *s = new DefaultAgentStrategy());
        bool addStrategic(unsigned x, unsigned y, Strategy *s = new DefaultAgentStrategy());
        bool addFood(const Position &position);
        bool addFood(unsigned x, unsigned y);
        bool addAdvantage(const Position &position);
        bool addAdvantage(unsigned x, unsigned y);
        const Surroundings getSurroundings() const;

        // gameplay methods
        static const ActionType reachSurroundings(const Position &from, const Position &to); // note: STAY by default
        static const Position randomPosition(const std::vector<int> &positions) { // note: from Surroundings as an array
            return __posRandomizer(positions);
        }

        bool isLegal(const ActionType &ac, const Position &pos) const;
        const Position move(const Position &pos, const ActionType &ac) const; // note: assumes legal, use with isLegal()
        void round();   // play a single round
        void play(bool verbose = false);    // play game until over

//        const Agent &winner(); // what if no winner or multiple winners?

        // Print as follows the state of the game after the last round:
        //
        // Round 1:
        // [F0   ][     ][T1   ]
        // [W2   ][     ][F3   ]
        // [     ][S4   ][     ]
        // Status: Playing...
        //
        // Round 5:
        // [     ][     ][     ]
        // [     ][T1   ][     ]
        // [     ][     ][     ]
        // Status: Over!
        //
        friend std::ostream &operator<<(std::ostream &os, const Game &game){
          /*
           os << "Round: " << static_cast<char>(game.__round);
            for (int j = 0; j < game.__height; ++j) {
                for (int j = 0; j < game.__height; ++j) {
                os << "[" <<  game.__grid[j] << "]";
            }
                os << "\n";
            }
            os << "Status "<< static_cast<char>(game.__status);
*/
            std::stringstream ss;
            ss << "Round: " << static_cast<char>(game.__round);
            for (int j = 0; j < game.__grid.size(); ++j) {
                ss << game.__grid[j] <<  ' ' ;
            }
            ss << "Status "<< static_cast<char>(game.__status);
            std::regex re("S[[:d:]]{1,}[ ]"); // ECMAScript, by default
            std::smatch m;
            std::string ss1;
            ss1 = ss.str();
            std::regex_search(ss1, m, re);
            os << ss1;

            return os;
        };
    };

}


#endif //PA5GAME_GAME_H
