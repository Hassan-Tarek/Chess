//
// Created by Hassan
//

#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// #include "Board.h"
class Board;           // forward declaration

enum class Color {
    WHITE = 0,
    BLACK
};

struct Position {
    int row;
    int col;
};

class Piece {
public:
    // constructor & destructor
    Piece(char, Color, Position);

    virtual ~Piece();

    // Accessors & mutators
    void setPosition(Position);

    Position getPosition() const;

    void setType(char type);

    char getType() const;

    void setColor(Color color);

    Color getColor() const;

    void setMoved(bool);

    bool hasMoved();

    // pure virtual function & virtual methods
    virtual std::vector<Position> getAllMoves(Board *) = 0;

    virtual std::vector<Position> getValidatedMoves(Board *);

protected:
    // utality functions
    bool inBounds(Position) const;

    bool testMove(Board *, Position);

private:
    char type;
    Position position;
    Color color;
    bool moved;

};

#endif // PIECE_H