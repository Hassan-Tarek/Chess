//
// Created by Hassan
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "../Board/Board.h"
#include "../Pieces/Piece.h"

enum class ErrorType {
    INVALID_INPUT = 0,
    INVALID_MOVE,
    ILLEGAL_MOVE,
    NULL_PIECE,
    OPPOSITE_PIECE
};

class Player {
public:
    // constructor & destructor
    Player(std::string, Color, Board *);

    ~Player();

    // public main functions
    void setName(std::string);

    std::string getName() const;

    Color getColor() const;

    std::string getInput();

    int inputState(std::string);

private:
    std::string name;
    Color color;
    Board *board;

    std::string getErrorMsg(ErrorType) const;

};

#endif // !PLAYER_H