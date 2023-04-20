//
// Created by Hassan
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "../Board/Board.h"

class Knight : public Piece {
public:
    // constructor & destructor
    Knight(Color color, Position);

    virtual ~Knight();

    // main public functions
    virtual std::vector<Position> getAllMoves(Board *);

private:
    const int NUM_OF_MOVES = 8;

};

#endif // !KNIGHT_H