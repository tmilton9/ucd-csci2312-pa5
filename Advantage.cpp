//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
#include "Advantage.h"


namespace Gaming {
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity): Resource(g, p, capacity) {

    }

    Advantage::~Advantage() {

    }

    void Advantage::print(std::ostream &os) const { //TODO

    }

    double Advantage::getCapacity() const {
        return __capacity;
    }

    double Advantage::consume() {
        Piece::finish();
        return ADVANTAGE_MULT_FACTOR;
    }


}