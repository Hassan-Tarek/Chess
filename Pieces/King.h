//
// Created by Hassan
//

#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "../Board/Board.h"

class King : public Piece {
public:
    // constructor & destructor
    King(Color, Position);

    virtual ~King();

    // public main functions
    virtual std::vector<Position> getAllMoves(Board *);

    virtual std::vector<Position> getValidatedMoves(Board *);

private:
    const int NUM_OF_MOVES = 8;

    void removeSquaresInBetweenKings(Board *, std::vector<Position> &);

    void removeCheckedMoves(Board *, std::vector<Position> &);

};

#endif // !KING_H