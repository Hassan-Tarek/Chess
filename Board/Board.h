//
// Created by Hassan
//

#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "Square.h"
#include "../Pieces/Piece.h"
#include "../Pieces/King.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Pawn.h"

#define console     GetStdHandle(STD_OUTPUT_HANDLE)
#define BLUE        SetConsoleTextAttribute(console, FOREGROUND_BLUE)
#define GREEN       SetConsoleTextAttribute(console, FOREGROUND_GREEN)
#define RED         SetConsoleTextAttribute(console, FOREGROUND_RED)
#define INTENSITY   SetConsoleTextAttribute(console, FOREGROUND_INTENSITY)

#define ROWS 8
#define COLS 8

class Board {
public:
    // constructor & destructor
    Board();

    virtual ~Board();

    // public main functions
    Position getKingPosition(Color);

    bool isCheck(Color);

    bool isCheckmate(Color);

    bool isStalemate(Color);

    bool isDraw();

    void draw();

    void fillSquare(Position, Piece *);

    Square *getSquare(Position);

    void setCapturedPieces(Color, std::vector<char>);

    std::vector<char> getCapturedPieces(Color);

    bool movePiece(Position, Position);

    void promotePiece();

private:
    Square board[ROWS][COLS];

    std::vector<char> whiteCapturedPieces;
    std::vector<char> blackCapturedPieces;

    std::vector<Position> getAllMoves(Color);

    std::vector<Position> getNonKingMoves(Color);

    void initializeBoard();

};

#endif // !BOARD_H