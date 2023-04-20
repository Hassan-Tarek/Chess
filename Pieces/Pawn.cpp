#include "Pawn.h"

/**
* Pawn class constructor
* @param color - the color of the Pawn Piece
* @param position - the row, col coordinates of the Pawn piece
*/
Pawn::Pawn(Color color, Position position)
        : Piece('P', color, position) {
}

/**
* Pawn class destructor
*/
Pawn::~Pawn() {
}

/**
* get all the available moves of the Pawn piece
* @param board - the game baord
* @return vector<Position> - a vector of all possible moves
*/
std::vector<Position> Pawn::getAllMoves(Board *board) {
    int r = this->getPosition().row;
    int c = this->getPosition().col;
    std::vector<Position> moves;
    int sign = board->getSquare(this->getPosition())->getPiece()->getColor() == Color::BLACK ? 1 : -1;
    for (int i = 0; i < NUM_OF_MOVES; i++) {
        int a = r, b = c;
        switch (i) {
            case 0:
                a += (sign * 1); // move one step
                break;
            case 1:
                a += (sign * 2); // move two steps
                break;
            case 2:
                a += (sign * 1), b += (sign * 1); // move diagonally to east
                break;
            case 3:
                a += (sign * 1), b -= (sign * 1); // move diagonally to west
                break;
            default:
                break;
        }

        Position position = {a, b};
        if (inBounds(position)) {
            if (board->getSquare(position)->getPiece() == NULL) { // the position is avaliable
                if (i == 0) {
                    moves.push_back(position);
                } else if (i == 1 && !hasMoved()) {
                    moves.push_back(position);
                }
            } else {
                if (b != c) {  // if move is diagonal one
                    if (board->getSquare(position)->getPiece()->getColor() != this->getColor()) {
                        // then i can capture this piece
                        moves.push_back(position);
                    }
                }
            }
        }
    }

    return moves;
}