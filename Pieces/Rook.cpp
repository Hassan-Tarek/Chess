#include "Rook.h"

/**
* Rook class constructor
* @param color - the color of the Rook Piece
* @param position - the row, col coordinates of the Rook piece
*/
Rook::Rook(Color color, Position position)
        : Piece('R', color, position) {
}

/**
* Rook class destructor
*/
Rook::~Rook() {
}

/**
* get all the available moves of the Rook piece
* @param board - the game baord
* @return vector<Position> - a vector of all possile moves
*/
std::vector<Position> Rook::getAllMoves(Board *board) {
    int r = this->getPosition().row;
    int c = this->getPosition().col;
    std::vector<Position> moves;
    for (int i = 0; i < NUM_OF_MOVES; i++) {
        for (int j = 1; j <= 8; j++) {
            int a = r, b = c;
            switch (i) {
                case 0:
                    a -= j;   // north
                    break;
                case 1:
                    b += j;   // east
                    break;
                case 2:
                    a += j;   // south
                    break;
                case 3:
                    b -= j;   // west
                    break;
                default:
                    break;
            }

            Position position = {a, b};
            if (inBounds(position)) {
                if (board->getSquare(position)->getPiece() == NULL) { // the position is avaliable
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