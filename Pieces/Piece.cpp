#include "Piece.h"
#include "../Board/Board.h"

/**
* Piece class constructor
* @param type - the type of the piece
* @param color - the color of the piece
* @param position - the x, y coordinates of the piece
*/
Piece::Piece(char type, Color color, Position position)
        : moved(false) {
    setType(type);
    setColor(color);
    setPosition(position);
}

/**
* piece class destructor
*/
Piece::~Piece() {
}

/**
* utility func that help to move a piece on a copy board
* @param board - the game board
* @param toPos - the row, col coordinates of the new position
* @return bool - true if move is a valid, false otherwise
*/
bool Piece::testMove(Board *board, Position toPos) {
    bool valid = true;

    // make a copy of the baord
    Board copiedBoard(*board);

    // move the piece
    copiedBoard.getSquare(this->position)->getPiece();
    copiedBoard.fillSquare(toPos, this);
    if (copiedBoard.isCheck(this->getColor()))
        valid = false;

    return valid;
}

/**
* get all valid positions of this piece
* @param board - the game board
* @return vector<Position> - a vector of all valid moves
*/
std::vector<Position> Piece::getValidatedMoves(Board *board) {
    std::vector<Position> pieceMoves = getAllMoves(board);
    std::vector<int> invalidIndexes;
    for (int i = 0; i < pieceMoves.size(); i++) {
        Position toPos = pieceMoves[i];

        bool valid = testMove(board, toPos);
        if (!valid)
            invalidIndexes.push_back(i);
    }

    // reverse the invalid indexes vector and erase all invalid moves from the list
    std::reverse(invalidIndexes.begin(), invalidIndexes.end());
    for (int index: invalidIndexes) {
        pieceMoves.erase(pieceMoves.begin() + index);
    }

    return pieceMoves;
}

/**
* set the position of the piece
* @param position - the x, y coordinates of the piece
*/
void Piece::setPosition(Position position) {
    this->position = position;
}

/**
* get the position of the current piece
* @return Position - the x, y coordinate of the piece
*/
Position Piece::getPosition() const {
    return position;
}

/**
* set the type of the piece
*/
void Piece::setType(char type) {
    this->type = type;
}

/**
* get the type of the piece
* @return char - the type of the current piece
*/
char Piece::getType() const {
    return type;
}

/**
* set the color of the current piece
*/
void Piece::setColor(Color color) {
    this->color = color;
}

/**
* get the color of the current piece
* @return Color - color of the piece
*/
Color Piece::getColor() const {
    return color;
}

/**
* set bool to true if the piece made a move
*/
void Piece::setMoved(bool moved) {
    this->moved = moved;
}

/**
* return true if the piece made a move, false otherwise
*/
bool Piece::hasMoved() {
    return moved;
}

/**
* check if the position is a valid position or not
* @return bool - true if the position is a valid one false otherwise
*/
bool Piece::inBounds(Position position) const {
    return position.row >= 0 && position.row < 8 &&
           position.col >= 0 && position.col < 8;
}
