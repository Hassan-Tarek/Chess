//
// Created by Hassan
//

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "../Board/Board.h"

class Bishop : public Piece {
public:
    // constructor & destructor
    Bishop(Color color, Position position);

    virtual ~Bishop();

    // public main functions
    virtual std::vector<Position> getAllMoves(Board *);

private:
    const int NUM_OF_MOVES = 4;

};

#endif // !BISHOP_H