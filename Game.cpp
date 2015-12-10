//
// Created by Travis Milton on 12/10/15.
//

#include "Game.h"
namespace Gaming {
    Gaming::Game::Game() {

    }

    Gaming::Game::Game(unsigned width, unsigned height, bool manual) {

    }

    Gaming::Game::Game(const ::Gaming::Game::Game &another) {

    }


    Gaming::Game::~Game() {

    }

    unsigned int Gaming::Game::getNumPieces() const {
     return 0;
    }

    unsigned int Gaming::Game::getNumAgents() const {
     return 0;
    }

    unsigned int Gaming::Game::getNumSimple() const {
     return 0;
    }

    unsigned int Gaming::Game::getNumStrategic() const {
     return 0;
    }

    unsigned int Gaming::Game::getNumResources() {
     return 0;
    }

    bool Gaming::Game::addSimple(const Position &position) {
     return false;
    }

    bool Gaming::Game::addSimple(unsigned x, unsigned y) {
     return false;
    }

    bool Gaming::Game::addStrategic(const Position &position, Strategy *s) {
     return false;
    }

    bool Gaming::Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
     return false;
    }

    bool Gaming::Game::addFood(const Position &position) {
     return false;
    }

    bool Gaming::Game::addFood(unsigned x, unsigned y) {
     return false;
    }

    bool Gaming::Game::addAdvantage(const Position &position) {
     return false;
    }

    bool Gaming::Game::addAdvantage(unsigned x, unsigned y) {
     return false;
    }

    const Gaming::Surroundings Gaming::Game::getSurroundings(const Position &pos) const {
     return Gaming::Surroundings();
    }

    const Gaming::ActionType Gaming::Game::reachSurroundings(const Position &from,
                                                             const Position &to) {
     return S;
    }

    bool Gaming::Game::isLegal(const ActionType &ac, const Position &pos) const {
     return false;
    }

    const Gaming::Position Gaming::Game::move(const Position &pos,
                                              const ActionType &ac) const {
     return Gaming::Position();
    }

    void Gaming::Game::round() {

    }

    void Gaming::Game::populate() {

    }

    void Gaming::Game::play(bool verbose) {

    }
}
