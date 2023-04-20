//
// Created by Hassan
//

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "../Board/Board.h"
#include "../Player/Player.h"

class Game {
public:
    // constructor & destructor
    Game(std::string = "Player1", std::string = "Player2");

    virtual ~Game();

    // public main functions
    void start(int);

private:
    Board *board;
    Player *player1;
    Player *player2;
    int turn;

    void play();

    int state(Player *);

    void load();

    void save();

};

#endif // !GAME_H
