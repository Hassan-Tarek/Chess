#include "Game.h"

/**
 * Game class constructor
 * @param firstPlayerName - the name of the first player 
 * @param secondPlayerName - the name of the second player
 */
Game::Game(std::string firstPlayerName, std::string secondPlayerName) {
    board = new Board();
    player1 = new Player(firstPlayerName, Color::WHITE, board);
    player2 = new Player(secondPlayerName, Color::BLACK, board);
    turn = 0;
}

/**
 * Game class destructor
 */
Game::~Game()  // free memory
{
    delete board;
    board = NULL;

    delete player1;
    player1 = NULL;

    delete player2;
    player2 = NULL;
}

/**
 * start the game
 * @param option - determine starting new game or loading the saved game
 */
void Game::start(int option) {
    if (option == 2)
        this->load();

    this->play();
}

/**
 * start playing
 */
void Game::play() {
    while (true) {
        // draw the board on the screen
        board->draw();

        switch (this->state(turn ? player2 : player1)) {
            case 0: {
                std::cout << (turn ? player1->getName() : player2->getName()) << " Won!" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }
            case 1: {
                std::cout << "Watch Your King!!" << std::endl;
                break;
            }
            case 2: {
                std::cout << "StaleMate!" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }
            case 3: {
                std::cout << "Draw!" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }
            default:
                break;
        }

        std::string input = "";
        while (input.size() != 1 && input.size() != 4) {
            std::cout << input << std::endl;
            input = turn == 0 ? player1->getInput() : player2->getInput();
        }

        if (input == "Q" || input == "q") {
            exit(EXIT_SUCCESS);
        } else if (input == "S" || input == "s") {
            this->save();
            char c = ' ';
            std::cout << "Do You Want To Continue Playing? [Y/N]: ";
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
                if (c != ' ')
                    std::cout << "Invalid Input!!" << std::endl;
                std::cin >> c;
            }

            switch (c) {
                case 'N':
                case 'n':
                    exit(EXIT_SUCCESS);
                    break;

                case 'Y':
                case 'y':
                    continue;   // continue playing
                    break;

                default:
                    break;
            }
        } else {
            int fromCol = input[0] - 'a';
            int fromRow = input[1] - '0' - 1;
            int toCol = input[2] - 'a';
            int toRow = input[3] - '0' - 1;

            board->movePiece(Position{fromRow, fromCol}, Position{toRow, toCol});
            turn ^= 1;
        }
    }
}

/**
 * get the current state of the game
 * @param player - the player
 * @return int - the current state of the game
 */
int Game::state(Player *player) {
    Color color = player->getColor();
    if (board->isCheckmate(color)) {
        return 0;
    } else if (board->isCheck(color)) {
        return 1;
    } else if (board->isStalemate(color)) {
        return 2;
    } else if (board->isDraw()) {
        return 3;
    } else {
        return 4;
    }
}

/**
 * load a game 
 */
void Game::load() {
    std::ifstream file("save.txt", std::ios::in);

    // check if the file exists or not
    if (!file) {
        std::cerr << "The file does not exist!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // set each player name
    std::string name1 = lines[0];
    std::string name2 = lines[1];

    // set each player name
    player1->setName(name1);
    player2->setName(name2);

    // read turn
    this->turn = std::stoi(lines[2]);

    // read board
    // from line 3 to 10
    for (int i = 3; i < 11; i++) {
        std::string line = lines[i];
        std::stringstream ss(line);
        std::string piece;

        int j = 0;
        while (std::getline(ss, piece, ' ')) {
            if (piece == "-") { // then assign this square to null
                board->fillSquare(Position{i - 3, j}, NULL);
            } else { // then assign this square to piece
                char type = piece[1];
                char color = piece[3];
                int moved = piece[9] == '1' ? 1 : 0;

                Color pieceColor = color == 'W' ? Color::WHITE : Color::BLACK;
                Position position = {i - 3, j};
                if (type == 'R')
                    board->fillSquare(position, new Rook(pieceColor, position));
                else if (type == 'N')
                    board->fillSquare(position, new Knight(pieceColor, position));
                else if (type == 'B')
                    board->fillSquare(position, new Bishop(pieceColor, position));
                else if (type == 'Q')
                    board->fillSquare(position, new Queen(pieceColor, position));
                else if (type == 'K')
                    board->fillSquare(position, new King(pieceColor, position));
                else if (type == 'P')
                    board->fillSquare(position, new Pawn(pieceColor, position));

                board->getSquare(position)->getPiece()->setMoved(moved);
            }
            ++j;
        }
    }

    // read all captured pieces
    // white captured pieces
    std::string pieces = lines[11];
    bool done = false;
    std::vector<char> capturedPieces;
    for (char c: pieces) {
        if (done)
            capturedPieces.push_back(c);
        if (c == ' ')
            done = true;
    }
    // set the white captured pieces
    board->setCapturedPieces(Color::WHITE, capturedPieces);

    // clear the capturedPieces vector
    capturedPieces.clear();

    // black captured pieces
    pieces = lines[12];
    done = false;
    for (char c: pieces) {
        if (done)
            capturedPieces.push_back(c);
        if (c == ' ')
            done = true;
    }

    // set the white captured pieces
    board->setCapturedPieces(Color::BLACK, capturedPieces);
}

/**
 * save the game
 */
void Game::save() {
    std::ofstream file("save.txt", std::ios::out);
    if (!file) {
        std::cerr << "File could not be opened!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // save the player1 name
    file << player1->getName() << std::endl;

    // save the player2 name
    file << player2->getName() << std::endl;

    // save the player turn
    file << turn << std::endl;

    // save board pieces
    // each piece has 3 main attributes (type, color, hasMoved)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j > 0)
                file << " ";

            Position position = {i, j};
            if (board->getSquare(position)->getPiece() != NULL) {
                std::string pieceColor =
                        board->getSquare(position)->getPiece()->getColor() == Color::BLACK ? "Black" : "White";
                file << "(" << board->getSquare(position)->getPiece()->getType() << "," << pieceColor << ","
                     << board->getSquare(position)->getPiece()->hasMoved() << ")";
            } else {
                file << "-";
            }
        }
        file << std::endl;
    }

    // save captured pieces of all of white player and black player
    file << "White: ";
    for (char c: board->getCapturedPieces(Color::WHITE)) {
        file << c;
    }
    file << std::endl;

    file << "Black: ";
    for (char c: board->getCapturedPieces(Color::BLACK)) {
        file << c;
    }
}