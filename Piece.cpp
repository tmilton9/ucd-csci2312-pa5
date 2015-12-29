//
// Created by Travis Milton on 12/10/15.
//
#include "Piece.h"

namespace Gaming {
	std::vector<Piece *> __grid;
	unsigned int Piece::__idGen = 0;

	//*****************************************************************************************
	// Method:    Piece
	// FullName:  Gaming::Piece::Piece
	// Access:    public
	// Returns:
	// Qualifier: : __game(__game)
	// Parameter: const Game & g
	// Parameter: const Position & p
	// Parameter: const Game & __game
	//*****************************************************************************************
	Piece::Piece(const Game &g, const Position &p, const Game &__game) : __game(__game) {
		__position = p;
		__id       = 0;
		__id       = __idGen++;
		__turned   = false;
		__finished = false;
		positioned = false;
	}

	//*****************************************************************************************
	// Method:    ~Piece
	// FullName:  Gaming::Piece::~Piece
	// Access:    virtual public
	// Returns:
	// Qualifier:
	// Info:      removes one number from idGen count
	//*****************************************************************************************
	Gaming::Piece::~Piece() {
		__idGen--;
	}

	//*****************************************************************************************
	// Method:    operator<<
	// FullName:  Gaming::operator<<
	// Access:    public
	// Returns:   std::ostream &
	// Qualifier:
	// Parameter: std::ostream & os
	// Parameter: const Piece & piece
	// Info:      when called from game this calls further up the hierarchy for the info
	//*****************************************************************************************
	std::ostream &operator<<(std::ostream &os, const Piece &piece) {
		piece.print(os);

		return os;
	};
}