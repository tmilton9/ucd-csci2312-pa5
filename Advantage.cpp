//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
namespace Gaming {
    Gaming::Advantage(const ::Gaming::Game &g, const ::Gaming::Position &p,
                                 double capacity) {

    }

    Gaming::~Advantage() {

    }

    void Gaming::print(std::ostream &os) const {

    }

    double Gaming::getCapacity() const {
        return Resource::getCapacity();
    }

    double Gaming::consume() {
        return Resource::consume();
    }


}