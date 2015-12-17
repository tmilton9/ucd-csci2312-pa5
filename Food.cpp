
//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
#include "Food.h"
namespace Gaming {
    const char Food::FOOD_ID = 'F';
    Food::Food( const Game &g, const Position &p, double capacity) : Resource( g, p, capacity) {

    }

    Food::~Food() {

    }

    void Food::print(std::ostream &os) const { //TODO

        os << FOOD_ID;

    }
}