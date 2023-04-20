//
// Created by Hassan
//

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "../Board/Board.h"

class Queen : public Piece {
public:
    // constructor & destructor
    Queen(Color, Position);

    virtual ~Queen();

    // public main functions
    virtual std::vector<Position> getAllMoves(Board *);

private:
    const int NUM_OF_MOVES = 8;

};

#endif // !QUEEN_H