//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Resource.h"
#include "Advantage.h"


namespace Gaming {
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g, p, capacity) {
          __capacity = capacity *ADVANTAGE_MULT_FACTOR;

    }

    Advantage::~Advantage() {

    }

    //************************************
    // Method:    print
    // FullName:  Gaming::Advantage::print
    // Access:    public 
    // Returns:   void
    // Qualifier: const
    // Parameter: std::ostream & os
    //************************************
    void Advantage::print(std::ostream &os) const { //TODO
		
		os << ADVANTAGE_ID << __id;

    }

    double Advantage::getCapacity() const {
        return __capacity;
    }

    double Advantage::consume() {
        Piece::finish();
        return ADVANTAGE_MULT_FACTOR;
    }


}