//
// Created by Hassan
//

#ifndef SQUARE_H
#define SQUARE_H

#include "../Pieces/Piece.h"

class Square {
public:
    // constructor & destructor
    Square();

    virtual ~Square();

    // public main functions
    void setPiece(Piece *);

    Piece *getPiece() const;

    void reset();

    Square &operator=(Piece *);

private:
    Piece *squarePiece;

};

#endif // !SQUARE_H