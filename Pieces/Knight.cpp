#include "Knight.h"

/**
* Knight class constructor
* @param color - the color of the Knight Piece
* @param position - the row, col coordinates of the Knight piece
*/
Knight::Knight(Color color, Position position)
        : Piece('N', color, position) {
}

/**
* Knight class destructor
*/
Knight::~Knight() {
}

/**
* get all the available moves of the Knight piece
* @param board - the game baord
* @return vector<Position> - a vector of all possible moves
*/
std::vector<Position> Knight::getAllMoves(Board *board) {
    int r = this->getPosition().row;
    int c = this->getPosition().col;
    std::vector<Position> moves;
    for (int i = 0; i < NUM_OF_MOVES; i++) {
        int a = r, b = c;
        switch (i) {
            case 0:
                a -= 2, b -= 1;
                break;
            case 1:
                a -= 2, b += 1;
                break;
            case 2:
                a -= 1, b -= 2;
                break;
            case 3:
                a -= 1, b += 2;
                break;
            case 4:
                a += 1, b -= 2;
                break;
            case 5:
                a += 1, b += 2;
                break;
            case 6:
                a += 2, b -= 1;
                break;
            case 7:
                a += 2, b += 1;
                break;
            default:
                break;
        }

        Position position = {a, b};
        if (inBounds(position)) {
            if (board->getSquare(position)->getPiece() == NULL) {
                moves.push_back(position);
            } else {
                if (board->getSquare(position)->getPiece()->getColor() !=
                    this->getColor()) {  // then i can capture this piece
                    moves.push_back(position);
                }
            }
        }

    }

    return moves;
}