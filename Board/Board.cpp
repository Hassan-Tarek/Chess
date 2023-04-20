#include "Board.h"

/**
* Board class constructor
*/
Board::Board() {
    initializeBoard();
}

/**
* Board class destructor
*/
Board::~Board() {
}

/**
* initialize the game board
*/
void Board::initializeBoard() {
    /// Rooks
    board[0][0] = new Rook(Color::BLACK, Position{0, 0});
    board[0][7] = new Rook(Color::BLACK, Position{0, 7});
    board[7][0] = new Rook(Color::WHITE, Position{7, 0});
    board[7][7] = new Rook(Color::WHITE, Position{7, 7});

    // Knights
    board[0][1] = new Knight(Color::BLACK, Position{0, 1});
    board[0][6] = new Knight(Color::BLACK, Position{0, 6});
    board[7][1] = new Knight(Color::WHITE, Position{7, 1});
    board[7][6] = new Knight(Color::WHITE, Position{7, 6});

    // Bishops
    board[0][2] = new Bishop(Color::BLACK, Position{0, 2});
    board[0][5] = new Bishop(Color::BLACK, Position{0, 5});
    board[7][2] = new Bishop(Color::WHITE, Position{7, 2});
    board[7][5] = new Bishop(Color::WHITE, Position{7, 5});

    // Queens
    board[0][3] = new Queen(Color::BLACK, Position{0, 3});
    board[7][3] = new Queen(Color::WHITE, Position{7, 3});

    // kings
    board[0][4] = new King(Color::BLACK, Position{0, 4});
    board[7][4] = new King(Color::WHITE, Position{7, 4});

    // Pawns
    // black Pawn
    board[1][0] = new Pawn(Color::BLACK, Position{1, 0});
    board[1][1] = new Pawn(Color::BLACK, Position{1, 1});
    board[1][2] = new Pawn(Color::BLACK, Position{1, 2});
    board[1][3] = new Pawn(Color::BLACK, Position{1, 3});
    board[1][4] = new Pawn(Color::BLACK, Position{1, 4});
    board[1][5] = new Pawn(Color::BLACK, Position{1, 5});
    board[1][6] = new Pawn(Color::BLACK, Position{1, 6});
    board[1][7] = new Pawn(Color::BLACK, Position{1, 7});

    // white Pawn
    board[6][0] = new Pawn(Color::WHITE, Position{6, 0});
    board[6][1] = new Pawn(Color::WHITE, Position{6, 1});
    board[6][2] = new Pawn(Color::WHITE, Position{6, 2});
    board[6][3] = new Pawn(Color::WHITE, Position{6, 3});
    board[6][4] = new Pawn(Color::WHITE, Position{6, 4});
    board[6][5] = new Pawn(Color::WHITE, Position{6, 5});
    board[6][6] = new Pawn(Color::WHITE, Position{6, 6});
    board[6][7] = new Pawn(Color::WHITE, Position{6, 7});
}

/**
* get all moves of the same color
* @param color - the color
* @return list of all moves of the same color
*/
std::vector<Position> Board::getAllMoves(Color color) {
    std::vector<Position> allMoves;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].getPiece() != NULL) {
                if (board[i][j].getPiece()->getColor() == color) {
                    std::vector<Position> pieceMoves = board[i][j].getPiece()->getValidatedMoves(this);
                    allMoves.insert(allMoves.end(), pieceMoves.begin(), pieceMoves.end());
                }
            }
        }
    }

    return allMoves;
}

/**
* get all non king's moves of a specific color
* @param color - the color
* @return - list of all the Non King's moves with specific color
*/
std::vector<Position> Board::getNonKingMoves(Color color) {
    std::vector<Position> moves;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].getPiece() != NULL) {
                if (board[i][j].getPiece()->getColor() == color &&
                    dynamic_cast<King *>(board[i][j].getPiece()) == NULL) {
                    std::vector<Position> pieceMoves = board[i][j].getPiece()->getAllMoves(this);
                    moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
                }
            }
        }
    }

    return moves;
}

/**
* get the king position
* @param color - the color of the king piece
*/
Position Board::getKingPosition(Color color) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].getPiece() != NULL) {
                if (board[i][j].getPiece()->getColor() == color &&
                    dynamic_cast<King *>(board[i][j].getPiece()) != NULL) {
                    return Position{i, j};
                }
            }
        }
    }

    return Position{-1, -1};
}

/**
* determine if the king is checked or not
* @param color - the color of the king piece
* @return bool - true if the king is checked false otherwise
*/
bool Board::isCheck(Color color) {
    // get the position of the king
    int row, col;
    row = getKingPosition(color).row;
    col = getKingPosition(color).col;

    // get all moves of all pieces of the other color if one move of them == the postion of the king then return true
    Color c = (color == Color::BLACK) ? Color::WHITE : Color::BLACK;
    std::vector<Position> positions = getNonKingMoves(c);
    for (Position position: positions) {
        if (position.row == row && position.col == col) {
            return true;
        }
    }

    // their is no check
    return false;
}

/**
* determine if there is checkmate or not
* @param color - the color of the king piece
* @return bool - true if checkmate, false otherwise
*/
bool Board::isCheckmate(Color color) {
    // get all moves and check if any piece can make a move
    // that make the king not checked if not then checkmate
    if (isCheck(color)) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j].getPiece() != NULL && board[i][j].getPiece()->getColor() == color) {
                    Position fromPos = board[i][j].getPiece()->getPosition();
                    std::vector<Position> pieceMoves = board[i][j].getPiece()->getValidatedMoves(this);
                    for (Position position: pieceMoves) {
                        Board copiedBoard(*this);
                        Position toPos = position;

                        // move the piece
                        copiedBoard.board[fromPos.row][fromPos.col].reset();
                        copiedBoard.board[toPos.row][toPos.col] = board[fromPos.row][fromPos.col];
                        if (!copiedBoard.isCheck(color)) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    return false;
}

/**
* determine if the player is in stalemate
* @param color - the color of the player
* @return bool - true if the player is in stalemate, false otherwise
*/
bool Board::isStalemate(Color color) {
    // if the king has no moves and there is no piece that can make a move
    // then its stalemate;
    if (isCheck(color))
        return false;

    if (getAllMoves(color).size() == 0)
        return true;
    else
        return false;
}

/**
* determine if its draw or not
* @return bool - true if its draw, false otherwise
*/
bool Board::isDraw() {
    // count the number of NULL squares
    // if the count == 62 then the board contain only the 2 kings
    int cnt = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].getPiece() == NULL) {
                cnt++;
            }
        }
    }

    if (cnt == 62)
        return true;
    else
        return false;
}

/**
* draw the board on the screen
*/
void Board::draw() {
    // clear the screen
    system("cls");

    BLUE;
    int cnt = 0;
    std::cout << "White's Captured Pieces: ";
    RED;
    for (char c: whiteCapturedPieces) {
        if (cnt == whiteCapturedPieces.size() - 1) {
            std::cout << c << std::endl;
        } else {
            std::cout << c << ", ";
            cnt++;
        }
    }
    if (whiteCapturedPieces.size() == 0) {
        std::cout << std::endl;
    }

    BLUE;
    cnt = 0;
    std::cout << "Black's Captured Pieces: ";
    GREEN;
    for (char c: blackCapturedPieces) {
        if (cnt == blackCapturedPieces.size() - 1) {
            std::cout << c << std::endl;
        } else {
            std::cout << c << ", ";
            cnt++;
        }
    }
    if (blackCapturedPieces.size() == 0)
        std::cout << std::endl;
    std::cout << std::endl << std::endl;

    INTENSITY;
    std::cout << "\t\t\t\t\t    A   B   C   D   E   F   G   H" << std::endl;
    BLUE;
    int indx1 = 0, indx2 = 0;
    for (int i = 0; i < ROWS; i++) {
        // change the color
        BLUE;
        std::cout << "\t\t\t\t\t  ";
        for (int j = 0; j < COLS; j++) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
        std::cout << "\t\t\t\t\t";

        INTENSITY;
        std::cout << i + 1 << " ";
        BLUE;

        for (int j = 0; j < COLS; j++) {
            BLUE;
            std::cout << "| ";

            Piece *piece = board[indx1][indx2++].getPiece();
            if (piece != NULL) {
                // change the color of the pieces
                if (piece->getColor() == Color::BLACK)
                    GREEN;

                if (piece->getColor() == Color::WHITE)
                    RED;

                std::cout << piece->getType() << " ";
            } else {
                if (indx1 % 2 == indx2 % 2)
                    std::cout << "- ";
                else
                    std::cout << "= ";
            }
        }
        BLUE;
        std::cout << "|";

        INTENSITY;
        std::cout << " " << i + 1 << std::endl;

        indx1++;
        indx2 = 0;
    }

    // draw last line
    BLUE;
    std::cout << "\t\t\t\t\t  ";
    for (int j = 0; j < COLS; j++) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;

    INTENSITY;
    std::cout << "\t\t\t\t\t    A   B   C   D   E   F   G   H" << std::endl;
}

/**
* reset the square and assign the square to piece
* @param position - the row, col coordinates of the square in the board
* @param piece - the piece that will be assgined to this square
*/
void Board::fillSquare(Position position, Piece *piece) {
    if (position.row >= 0 && position.row < 8 && position.col >= 0 && position.col < 8) {  // validate position
        board[position.row][position.col].reset();
        board[position.row][position.col].setPiece(piece);
    }
}

/**
* get the square of the chess board
* @param position - the row, col coordinates of the square
* @return - a pointer to the square
*/
Square *Board::getSquare(Position position) {
    return &board[position.row][position.col];
}

/**
* set the captured pieces of a specific color 
* @param color - the pieces color
* @param pieces - all captured pieces of this specific color
*/
void Board::setCapturedPieces(Color color, std::vector<char> pieces) {
    if (color == Color::BLACK) {
        blackCapturedPieces = pieces;
    } else {
        whiteCapturedPieces = pieces;
    }
}

/**
* get all the captured pieces of a spacific color
* @param color - the pieces color
* @return vector<char> - all captured pieces of this specific color
*/
std::vector<char> Board::getCapturedPieces(Color color) {
    if (color == Color::BLACK) {
        return this->blackCapturedPieces;
    } else {
        return this->whiteCapturedPieces;
    }
}

/**
* move a piece
* @param fromPos - the row, col coordinate of the piece
* @param toPos - the row, col coordinate of the new position
* @return bool - true if the piece moved, false otherwise
*/
bool Board::movePiece(Position fromPos, Position toPos) {
    bool moved = false;
    Piece *piece = board[fromPos.row][fromPos.col].getPiece();
    Color pieceColor = piece->getColor();

    if (piece != NULL) {
        // get all valid moves
        std::vector<Position> validMoves = piece->getValidatedMoves(this);
        bool valid = false;
        for (Position position: validMoves) {
            if (position.row == toPos.row && position.col == toPos.col) {
                valid = true;
                break;
            }
        }

        if (valid) {
            if (board[toPos.row][toPos.col].getPiece() != NULL &&
                board[toPos.row][toPos.col].getPiece()->getColor() != piece->getColor()) {
                if (pieceColor == Color::WHITE) {
                    blackCapturedPieces.push_back(board[toPos.row][toPos.col].getPiece()->getType());
                } else {
                    whiteCapturedPieces.push_back(board[toPos.row][toPos.col].getPiece()->getType());
                }
            }

            if (dynamic_cast<King *>(piece) != NULL && piece->hasMoved() == false &&
                (toPos.row == fromPos.row && toPos.col - 3 == fromPos.col ||
                 toPos.row == fromPos.row && toPos.col + 4 == fromPos.col)) {

                Position rookPosition;
                int kRow, kCol, rRow, rCol;
                if (toPos.col > fromPos.col)
                    kRow = toPos.row, kCol = 6, rRow = toPos.row, rCol = 5, rookPosition = {fromPos.row, 7};
                else
                    kRow = toPos.row, kCol = 2, rRow = toPos.row, rCol = 3, rookPosition = {fromPos.row, 0};

                // move King
                board[fromPos.row][fromPos.col].reset();
                board[kRow][kCol] = piece;
                piece->setPosition(Position{kRow, kCol});

                // move Rook
                board[rookPosition.row][rookPosition.col].reset();
                board[rRow][rCol] = new Rook(piece->getColor(), Position{rRow, rCol});
            } else {
                board[fromPos.row][fromPos.col].reset();
                board[toPos.row][toPos.col] = piece;
                piece->setPosition(toPos);
            }
            moved = true;
            piece->setMoved(true);

            // promote pawn if possible
            promotePiece();
        }
    }

    return moved;
}

/**
* promote pawn pieces if possible
*/
void Board::promotePiece() {
    // check the first & last row
    int r = -1, c = -1;
    for (int i = 0; i < 8; i++) {
        if (board[0][i].getPiece() != NULL) {
            if (dynamic_cast<Pawn *>(board[0][i].getPiece()) != NULL &&
                board[0][i].getPiece()->getColor() == Color::WHITE) {
                r = 0, c = i;
                break;
            }
        }
        if (board[7][i].getPiece() != NULL) {
            if (dynamic_cast<Pawn *>(board[7][i].getPiece()) != NULL &&
                board[7][i].getPiece()->getColor() == Color::BLACK) {
                r = 7, c = i;
                break;
            }
        }
    }

    if (r >= 0 && r < 8 && c >= 0 && c < 8) {
        char choice = ' ';
        while (choice != 'R' && choice != 'Q' && choice != 'N' && choice != 'B') {
            std::cout << "Choose a Piece ['R', 'Q', 'N', 'B']: ";
            std::cin >> choice;
        }

        // clear the square
        board[r][c].reset();

        Color color = r == 0 ? Color::WHITE : Color::BLACK;
        if (choice == 'R') {
            board[r][c] = new Rook(color, Position{r, c});
        } else if (choice == 'Q') {
            board[r][c] = new Queen(color, Position{r, c});
        } else if (choice == 'N') {
            board[r][c] = new Knight(color, Position{r, c});
        } else if (choice == 'B') {
            board[r][c] = new Bishop(color, Position{r, c});
        }
    }
}