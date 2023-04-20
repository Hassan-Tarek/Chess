#include "Queen.h"

/**
* Queen class constructor
* @param color - the color of the Queen Piece
* @param position - the row, col coordinates of the Queen piece
*/
Queen::Queen(Color color, Position position)
        : Piece('Q', color, position) {
}

/**
* Queen class destructor
*/
Queen::~Queen() {
}

/**
* get all the available moves of the Queen piece
* @param board - the game baord
* @return vector<Position> - a vector of all possible moves
*/
std::vector<Position> Queen::getAllMoves(Board *board) {
    int r = this->getPosition().row;
    int c = this->getPosition().col;
    std::vector<Position> moves;
    for (int i = 0; i < NUM_OF_MOVES; i++) {
        for (int j = 1; j <= 8; j++) {
            int a = r, b = c;
            switch (i) {
                case 0:
                    a -= j, b -= j;   // north-west
                    break;
                case 1:
                    a -= j, b += j;   // north-east
                    break;
                case 2:
                    a -= j;           // north
                    break;
                case 3:
                    b += j;           // east
                    break;
                case 4:
                    b -= j;           // west
                    break;
                case 5:
                    a += j;           // south
                    break;
                case 6:
                    a += j, b -= j;   // south-west
                    break;
                case 7:
                    a += j, b += j;   // south-east
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
                        this->getColor()) { // then i can capture this piece
                        moves.push_back(position);
                        break;
                    } else {
                        break;
                    }
                }
            } else {
                break;
            }
        }
    }

    return moves;
}