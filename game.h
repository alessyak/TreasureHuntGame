#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
    Player& player;
    int maxMoves;
    int pathLength;
    int* pathBombs;
    int* pathTreasures;
    int currentPlayerPosition;
public:
    Game(Player& player);
    virtual ~Game();
    void configureGame();
    void printGameInfo();
    void playGame();
    void printGameBoard();
};

#endif