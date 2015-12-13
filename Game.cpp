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
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game() {
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __round = 0;
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        __grid;
        manual = true;
        __verbose = false;


    }

    Game::Game(unsigned width, unsigned height, bool manual):manual(true) {
        __width = width;
        __height = height;
        __round = 0;
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        __grid;
        __verbose = false;
        if (!manual){
            populate();
        }
    }

    Game::Game(const Game &another) {
        __width = another.__width;
        __height = another.__height;
        __round = another.__round;
        __numInitAgents = another.__numInitAgents;
        __numInitResources = another.__numInitResources;
        __grid = another.__grid;
        manual = another.manual;
        __verbose = another.__verbose;
    }


    Game::~Game() {
        
    }

    unsigned int Game::getNumPieces() const {
        unsigned int numPieces = 0;
        numPieces += numAdvantages;
        numPieces += numFoods;
        numPieces += numSimple;
        numPieces += numStrategic;
     return numPieces;
    }

    unsigned int Game::getNumAgents() const {
        unsigned int numAgents =0 ;
        numAgents += numStrategic;
        numAgents += numSimple;
     return numAgents;
    }

    unsigned int Game::getNumSimple() const {
     return numSimple;
    }

    unsigned int Game::getNumStrategic() const {
     return numStrategic;
    }

    unsigned int Game::getNumResources() {
        unsigned int numResources = 0;
        numResources += numFoods;
        numResources += numAdvantages;
     return numResources;
    }

    bool Game::addSimple(const Position &position) {
        Simple(*this, position, STARTING_AGENT_ENERGY);
     return true;
    }

    bool Game::addSimple(unsigned x, unsigned y) {
        Position position(x,y);
        Simple(*this, position, STARTING_AGENT_ENERGY);
     return true;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {
        Strategic(*this, position, STARTING_AGENT_ENERGY,s);
        return true;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        Position position(x,y);
        Strategic(*this, position, STARTING_AGENT_ENERGY,s);
     return true;
    }

    bool Game::addFood(const Position &position) {
        Food(*this, position, STARTING_RESOURCE_CAPACITY);
     return true;
    }

    bool Game::addFood(unsigned x, unsigned y) {
        Position position(x,y);
        Food(*this, position, STARTING_RESOURCE_CAPACITY);
     return true;
    }

    bool Game::addAdvantage(const Position &position) {
        Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
     return true;
    }

    bool Game::addAdvantage(unsigned x, unsigned y) {
        Position position(x,y);
        Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
     return true;
    }

    const Surroundings Gaming::Game::getSurroundings() const {
     return Surroundings();
    }

    const ActionType Gaming::Game::reachSurroundings(const Position &from, const Position &to) {

        if (from.x < to.x) { // N
            if (from.y == to.y)return N;
            if (from.y < to.y)return NW;
            if (from.y > to.y)return NE;
        }
        if (from.x == to.x){ // E or W
            if (from.y == to.y)return STAY;
            if (from.y < to.y)return W;
            if (from.y > to.y)return E;
        }
        if (from.x > to.x){ // S
            if (from.y == to.y)return S;
            if (from.y < to.y)return SW;
            if (from.y > to.y)return SE;
        }
        else return STAY;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        bool legal = true;

        auto Su = getSurroundings();
        switch (ac){
           case N: {
               if (Su.array[1] == INACCESSIBLE){
                   legal = false; }break;
           }
            case NE:{
                if (Su.array[2] == INACCESSIBLE){
                    legal = false; }break;
            }
            case NW:{
                if (Su.array[0] == INACCESSIBLE){
                    legal = false; }break;
            }
            case E:{
                if (Su.array[5] == INACCESSIBLE){
                    legal = false; }break;
            }
            case W:{
                if (Su.array[3] == INACCESSIBLE){
                    legal = false; }break;
            }
            case SE:{
                if (Su.array[8] == INACCESSIBLE){
                    legal = false; }break;
            }
            case SW:{
                if (Su.array[6] == INACCESSIBLE){
                    legal = false; }break;
            }
            case S:{
                if (Su.array[7] == INACCESSIBLE){
                    legal = false; }break;
            }
            case STAY:{
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

            switch (ac){
                case N: posN.x = x-1; break;
                case NE:posN.x = x-1;posN.y = y+1;break;
                case NW:posN.x = x-1;posN.y = y-1;break;
                case E:posN.y = y+1;break;
                case W:posN.y = y-1;break;
                case SE:posN.x = x+1;posN.y = y+1;break;
                case SW:posN.x = x+1;posN.y = y-1;break;
                case S:posN.x = x+1;break;
                case STAY:posN = pos;break;
            }
            int tot, tot2;
            tot = (x*__width) + y;
            tot2 = (posN.x*__width) + posN.y;
            __grid.begin();
            if (__grid.at(tot2)->getType() == STRATEGIC){
                __grid.at(tot)->interact((Agent *) __grid.at(tot2));
            }
            if (__grid.at(tot2)->getType() == ADVANTAGE){
                __grid.at(tot)->interact((Advantage *) __grid.at(tot2));
            }
            if (__grid.at(tot2)->getType() == FOOD){
                __grid.at(tot)->interact((Food *) __grid.at(tot2));
            }
            if(!__grid.at(tot)->isViable()) {__grid.at(tot)->~Piece();__grid.at(tot);}
            if(!__grid.at(tot2)->isViable()){__grid.at(tot2)->~Piece();__grid.at(tot2);}
        }

     return posN;
    }

    void Game::round() {

    }

    void Game::populate() {
        if (!manual) {
            numPositions = __height * __width;
            for (unsigned int j = 0; j < numPositions; ++j) {
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
                    numStrategic++;
                }
            }

            // populate Simple agents
            while (numSimpleP > 0) {
                int i = d(gen); // random index in the grid vector
                if (__grid[i] == nullptr) { // is position empty
                    Position pos(i / __width, i % __width);
                    __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                    numSimpleP--;
                    numSimple++;
                }
            }

            // populate Food Resources
            while (numFoodsP > 0) {
                int i = d(gen); // random index in the grid vector
                if (__grid[i] == nullptr) { // is position empty
                    Position pos(i / __width, i % __width);
                    __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                    numFoodsP--;
                    numFoods++;
                }

            }
            // populate Advantage Reasorces
            while (numAdvantagesP > 0) {
                int i = d(gen); // random index in the grid vector
                if (__grid[i] == nullptr) { // is position empty
                    Position pos(i / __width, i % __width);
                    __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                    numAdvantagesP--;
                    numAdvantages++;
                }

            }
        }
        if (manual) {
            numPositions = __height * __width;
            for (unsigned int j = 0; j < numPositions; ++j) {
                __grid.push_back(nullptr);
            }

        }
    }
    void Game::play(bool verbose) {

    }

}
