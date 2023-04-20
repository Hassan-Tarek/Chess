#include <iostream>

#include "Game/Game.h"

int main() {
    INTENSITY;
    int option = 0;
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t\t1- New Game" << std::endl;
    std::cout << "\t\t\t\t\t\t2- Load Game" << std::endl;
    while (option != 1 && option != 2) {
        std::cout << "\t\t\t\t\t\t   Enter Your Choice: ";
        std::cin >> option;
    }

    // clear the screen
    system("cls");
    std::string name1 = "";
    std::string name2 = "";
    if (option != 2) { // ask players for their names
        std::cout << "First Player Name: ";
        std::cin >> name1;
        std::cout << "Second Player Name: ";
        std::cin >> name2;
    }

    // create and start the game
    Game game(name1, name2);
    game.start(option);
}