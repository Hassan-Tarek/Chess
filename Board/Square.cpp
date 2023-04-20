#include "Square.h"

/**
* Square class constructor
*/
Square::Square()
        : squarePiece(NULL) {
}

/**
* Square class destructor
*/
Square::~Square() {
}

/**
* set the piece
* @param piece - the piece of the square or NULL if the sqaure is empty
*/
void Square::setPiece(Piece *piece) {
    this->squarePiece = piece;
}

/**
* get the piece in this square
* @return - the piece in this square or NULL
*/
Piece *Square::getPiece() const {
    return squarePiece;
}

/**
* reset the current square
*/
void Square::reset() {
    squarePiece = NULL;
}

Square &Square::operator=(Piece *piece) {
    this->squarePiece = piece;
    return *this;
}