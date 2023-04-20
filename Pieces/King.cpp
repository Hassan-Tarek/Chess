#include "King.h"

/**
* King class constructor
* @param color - the color of the King Piece
* @param position - the row, col coordinate of the king piece
*/
King::King(Color color, Position position)
        : Piece('K', color, position) {
}

/**
* King class destructor
*/
King::~King() {}

/**
* get all the available moves of the king piece
* @param board - the game baord
* @return vector<Position> - a vector of all possible moves
*/
std::vector<Position> King::getAllMoves(Board *board) {
    int r = this->getPosition().row;
    int c = this->getPosition().col;
    std::vector<Position> moves;
    for (int i = 0; i < NUM_OF_MOVES; i++) {
        int a = r, b = c;
        switch (i) {
            case 0:
                a += 1;              // north
                break;
            case 1:
                a += 1, b += 1;      // north-east
                break;
            case 2:
                a += 1, b -= 1;      // north-west
                break;
            case 3:
                a -= 1;              // south
                break;
            case 4:
                a -= 1, b -= 1;      // south-west
                break;
            case 5:
                a -= 1, b += 1;      // south-east
                break;
            case 6:
                b += 1;              // east
                break;
            case 7:
                b -= 1;              // west
                break;
            default:
                break;
        }

        Position position = {a, b};
        if (inBounds(position)) {
            if (board->getSquare(position)->getPiece() == NULL) {
                moves.push_back(position);
            } else {
                if (board->getSquare(position)->getPiece()->getColor() != this->getColor()) {
                    moves.push_back(position);
                }
            }
        }
    }

    // handle casle moves
    if (this->hasMoved() == false) {
        // check right
        if (board->getSquare(Position{this->getPosition().row, this->getPosition().col + 1})->getPiece() == NULL &&
            board->getSquare(Position{this->getPosition().row, this->getPosition().col + 2})->getPiece() == NULL &&
            dynamic_cast<Rook *>(board->getSquare(
                    Position{this->getPosition().row, this->getPosition().col + 3})->getPiece()) != NULL) {
            if (this->testMove(board, Position{this->getPosition().row, this->getPosition().col + 2})) {
                // add position to vector
                moves.push_back(Position{this->getPosition().row, this->getPosition().col + 3});
            }
        }

        // check left
        if (board->getSquare(Position{this->getPosition().row, this->getPosition().col - 1})->getPiece() == NULL &&
            board->getSquare(Position{this->getPosition().row, this->getPosition().col - 2})->getPiece() == NULL &&
            board->getSquare(Position{this->getPosition().row, this->getPosition().col - 3})->getPiece() == NULL &&
            dynamic_cast<Rook *>(board->getSquare(
                    Position{this->getPosition().row, this->getPosition().col - 4})->getPiece()) != NULL) {
            if (this->testMove(board, Position{this->getPosition().row, this->getPosition().col - 3})) {
                // add position to vector
                moves.push_back(Position{this->getPosition().row, this->getPosition().col - 4});
            }
        }
    }

    return moves;
}

/**
* get all valid positions of this king piece
* @param board - the game board
* @return vector<Position> - a vector of all valid moves
*/
std::vector<Position> King::getValidatedMoves(Board *board) {
    std::vector<Position> moves = this->getAllMoves(board);

    // remove all invalid moves
    removeSquaresInBetweenKings(board, moves);
    removeCheckedMoves(board, moves);

    return moves;
}


/**
* remove all squares that seperate the two kings
* @param board - the game board
* @param moves - a vector of all the posible moves of the king
*/
void King::removeSquaresInBetweenKings(Board *board, std::vector<Position> &moves) {
    std::vector<int> invalidIndexes;
    Color color = this->getColor() == Color::BLACK ? Color::WHITE : Color::BLACK;

    // all the sqaure the surround the other king position
    std::vector<Position> invalidPositions;

    int c = board->getKingPosition(color).row;
    int d = board->getKingPosition(color).col;
    invalidPositions = {Position{c, d - 1}, Position{c, d + 1}, Position{c + 1, d + 1},
                        Position{c - 1, d}, Position{c + 1, d}, Position{c - 1, d - 1},
                        Position{c + 1, d - 1}, Position{c - 1, d + 1}};

    for (int i = 0; i < invalidPositions.size(); i++) {
        if (!inBounds(invalidPositions[i])) {
            invalidIndexes.push_back(i);
        }
    }

    // reverse the invalidIndexes vector
    std::reverse(invalidIndexes.begin(), invalidIndexes.end());
    for (int index: invalidIndexes) {
        invalidPositions.erase(invalidPositions.begin() + index);
    }

    // clear the invalidIndexes vector
    invalidIndexes.clear();

    for (int i = 0; i < moves.size(); i++) {
        for (int j = 0; j < invalidPositions.size(); j++) {
            if (moves[i].row == invalidPositions[j].row && moves[i].col == invalidPositions[j].col) {
                invalidIndexes.push_back(i);
            }
        }
    }

    // reverse the invalidIndexes vector
    std::reverse(invalidIndexes.begin(), invalidIndexes.end());

    // remove the invalid moves
    for (int index: invalidIndexes) {
        moves.erase(moves.begin() + index);
    }

    invalidIndexes.clear();
}

/**
* remove all moves that make the king checked
* @param board - the game board
* @param moves - a vector of all the posible moves of the king
*/
void King::removeCheckedMoves(Board *board, std::vector<Position> &moves) {
    std::vector<int> invalidIndexes;
    Position fromPos = this->getPosition();

    for (int i = 0; i < moves.size(); i++) {
        Position toPos = moves[i];

        Board *copiedBoard = new Board(*board);
        // test move the king
        bool valid = this->testMove(copiedBoard, toPos);
        if (!valid) { // if !valid then this move will make the king is checked so delete it
            // add the index to the invalid indexes list
            invalidIndexes.push_back(i);
        }

        delete copiedBoard;
        copiedBoard = NULL;
    }

    // reverse the invalidIndexes vector
    std::reverse(invalidIndexes.begin(), invalidIndexes.end());

    // remove the invalid moves
    for (int index: invalidIndexes) {
        moves.erase(moves.begin() + index);
    }

    invalidIndexes.clear();
}