//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
namespace Gaming {
    Gaming::Food::Food(const ::Gaming::Food::Game &g, const ::Gaming::Food::Position &p, double capacity) {

    }

    Gaming::Food::~Food() {

    }

    void Gaming::Food::print(std::ostream &os) const {
      Resource::print(os);
    }
}