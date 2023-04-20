//
// Created by Hassan
//

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "../Board/Board.h"

class Pawn : public Piece {
public:
    // constructors & destructors
    Pawn(Color color, Position);

    virtual ~Pawn();

    // public main functions
    virtual std::vector<Position> getAllMoves(Board *);

private:
    const int NUM_OF_MOVES = 4;

};

#endif // !PAWN_H