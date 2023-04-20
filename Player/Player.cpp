#include "Player.h"

/**
* Player class constructor
* @param name - Player Name
* @param color - the color of the player
* @param board - the board that the player play on
*/
Player::Player(std::string name, Color color, Board *board)
        : color(color), board(board) {
    this->setName(name);
}

/**
* Player class destructor
*/
Player::~Player() {
}

/**
* get the player input
* @return string - the player input or error message if the input is not valid
*/
std::string Player::getInput() {
    std::string input;
    std::cout << "Enter a move in the form \"A1B1\" or \"S\" to Save \"Q\" to Quit.\n";
    std::cout << this->getName() << "\'s turn " << (color == Color::WHITE ? "(White): " : "(Black): ");
    std::cin >> input;

    int state = inputState(input);
    switch (state) {
        case 0:
            return input;
            break;
        case 1:
            return this->getErrorMsg(ErrorType::INVALID_INPUT);
            break;
        case 2:
            return this->getErrorMsg(ErrorType::INVALID_MOVE);
            break;
        case 3:
            return this->getErrorMsg(ErrorType::ILLEGAL_MOVE);
            break;
        case 4:
            return this->getErrorMsg(ErrorType::NULL_PIECE);
            break;
        case 5:
            return this->getErrorMsg(ErrorType::OPPOSITE_PIECE);
            break;
        default:
            return NULL;
            break;
    }
}

// 0 valid
// 1 invalid input
// 2 invalid move
// 3 illegal move
// 4 null piece
// 5 opposite piece
/**
* @param input - the player input
* @return int - the state of the player input
*/
int Player::inputState(std::string input) {
    int state;
    if (input.size() != 4 && input.size() != 1) {
        state = 1;
    } else {
        state = 2;
        if (input == "Q" || input == "q" || input == "S" || input == "s") {
            state = 0;
        } else if (input.size() == 4) {
            bool valid = isalpha(input[0]) && isalpha(input[2]) && isdigit(input[1]) && isdigit(input[3]);
            if (valid) {
                input[0] = tolower(input[0]);
                input[2] = tolower(input[2]);
                bool valid1 = (input[0] <= 'h' && input[0] >= 'a') && (input[2] >= 'a' && input[2] <= 'h');
                bool valid2 = (input[1] >= '1' && input[1] <= '8') && (input[3] >= '1' && input[3] <= '8');

                if (valid1 && valid2) {
                    int fromCol = input[0] - 'a';
                    int fromRow = input[1] - '0' - 1;
                    int toCol = input[2] - 'a';
                    int toRow = input[3] - '0' - 1;

                    Piece *piece = board->getSquare(Position{fromRow, fromCol})->getPiece();
                    if (piece == NULL) {
                        state = 4;
                    } else if (piece->getColor() != this->getColor()) {
                        state = 5;
                    }

                    std::vector<Position> moves = piece->getValidatedMoves(board);
                    bool valid = false;
                    for (Position move: moves) {
                        if (move.row == toRow && move.col == toCol) {
                            valid = true;
                            break;
                        }
                    }

                    state = valid ? 0 : 3;
                }
            }
        }
    }
    return state;
}

/**
* get an error message
*/
std::string Player::getErrorMsg(ErrorType type) const {
    std::string message = "";
    switch (type) {
        case ErrorType::INVALID_INPUT:
            message = "Inalid Input!";
            break;
        case ErrorType::INVALID_MOVE:
            message = "Invalid Move!";
            break;
        case ErrorType::ILLEGAL_MOVE:
            message = "Illegal Move!";
            break;
        case ErrorType::NULL_PIECE:
            message = "The square has no piece!";
            break;
        case ErrorType::OPPOSITE_PIECE:
            message = "This piece belong to the other player!";
            break;
        default:
            break;
    }
    return message;
}

/**
* set player name
* @param name - validate and set the player name
*/
void Player::setName(std::string name) {
    if (name != "") {
        name[0] = toupper(name[0]);
        this->name = name;
    }
}

/**
* get player name
* @return string - the player name
*/
std::string Player::getName() const {
    return name;
}

/**
* get player color
* @return Color - the player color
*/
Color Player::getColor() const {
    return color;
}