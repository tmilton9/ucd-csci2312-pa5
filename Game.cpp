//
// Created by Travis Milton on 12/10/15.
//

#include "Game.h"
namespace Gaming {
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game() {

    }

    Game::Game(unsigned width, unsigned height, bool manual) {

    }

    Game::Game(const Game &another) {

    }


    Game::~Game() {

    }

    unsigned int Game::getNumPieces() const {
     return 0;
    }

    unsigned int Game::getNumAgents() const {
     return 0;
    }

    unsigned int Game::getNumSimple() const {
     return 0;
    }

    unsigned int Game::getNumStrategic() const {
     return 0;
    }

    unsigned int Game::getNumResources() {
     return 0;
    }

    bool Game::addSimple(const Position &position) {
     return false;
    }

    bool Game::addSimple(unsigned x, unsigned y) {
     return false;
    }

    bool Game::addStrategic(const Position &position, Strategy *s) {
     return false;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
     return false;
    }

    bool Game::addFood(const Position &position) {
     return false;
    }

    bool Game::addFood(unsigned x, unsigned y) {
     return false;
    }

    bool Game::addAdvantage(const Position &position) {
     return false;
    }

    bool Game::addAdvantage(unsigned x, unsigned y) {
     return false;
    }

    const Surroundings Gaming::Game::getSurroundings(const Position &pos) const {
     return Surroundings();
    }

    const ActionType Gaming::Game::reachSurroundings(const Position &from,
                                                             const Position &to) {
     return S;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
     return false;
    }

    const Position Gaming::Game::move(const Position &pos,
                                              const ActionType &ac) const {
     return Position();
    }

    void Game::round() {

    }

    void Game::populate() {

    }

    void Game::play(bool verbose) {

    }

}
