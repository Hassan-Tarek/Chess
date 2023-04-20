//
// Created by Hassan
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "../Board/Board.h"

class Rook : public Piece {
public:
    // constructor & destructor
    Rook(Color, Position);

    virtual ~Rook();

    // main public functions
    virtual std::vector<Position> getAllMoves(Board *);

private:
    const int NUM_OF_MOVES = 4;

};

#endif // !ROOK_H