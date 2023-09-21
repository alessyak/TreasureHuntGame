#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Player.h"
#include "Game.h"

using namespace std;

int main() {
    cout << "================================" << endl;
    cout << "         Treasure Hunt!" << endl;
    cout << "================================" << endl << endl;

    Player player;
    Game game(player);

    player.configurePlayer();
    game.configureGame();

    cout << "GAME configuration set-up is complete..." << endl << endl;
    cout << "------------------------------------" << endl;
    cout << "TREASURE HUNT Configuration Settings" << endl;
    cout << "------------------------------------" << endl;
    player.printPlayerInfo();
    game.printGameInfo();

    cout << "====================================" << endl;
    cout << "~ Get ready to play TREASURE HUNT! ~" << endl;
    cout << "====================================" << endl;

    game.playGame();

    cout << endl << "##################" << endl;
    cout << "#   Game over!   #" << endl;
    cout << "##################" << endl << endl;
    cout << "You should play again and try to beat your score!" << endl;

    return 0;
}