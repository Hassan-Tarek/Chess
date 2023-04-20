#include "Bishop.h"

/**
* Bishop class constructor
* @param color - the color of the Bishop Piece
* @param position - the row, col coordinates of the Bishop piece
*/
Bishop::Bishop(Color color, Position position)
        : Piece('B', color, position) {
}

/**
* Bishop class destructor
*/
Bishop::~Bishop() {
}

/**
* get all the available moves of the Bishop piece
* @param board - the game baord
* @return vector<Position> - a vector of all possible moves
*/
std::vector<Position> Bishop::getAllMoves(Board *board) {
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
                    a += j, b -= j;   // south-west
                    break;
                case 3:
                    a += j, b += j;   // south-east
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