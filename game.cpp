#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include "Game.h"

using namespace std;

Game::Game(Player& playerRef) : player(playerRef), currentPlayerPosition(0) {
    maxMoves = 0;
    pathLength = 0;
    pathBombs = nullptr;
    pathTreasures = nullptr;
}

Game::~Game() {
    delete[] pathBombs;
    delete[] pathTreasures;
}

void Game::configureGame() {
    cout << endl << "GAME Configuration" << endl;
    cout << "------------------" << endl;

    do {
        cout << "Set the path length (a multiple of 5 between 10-70): ";
        cin >> pathLength;

        if (pathLength % Multiplier != 0 || pathLength < MIN_Path || pathLength > MAX_Path)
            cout << "Must be a multiple of 5 and between 10-70!" << endl;

    } while (!(pathLength % Multiplier == 0 && pathLength >= MIN_Path && pathLength <= MAX_Path));

    do {
        cout << "Set the limit for the number of moves allowed: ";
        cin >> maxMoves;

        if (maxMoves < player.getLives() || maxMoves > pathLength * 0.75 + 0.05)
            cout << "Value must be between " << player.getLives() << " and " << pathLength * 0.75 + 0.05 << endl;

    } while (!(maxMoves >= player.getLives() && maxMoves <= pathLength * 0.75));

    pathBombs = new int[pathLength];
    pathTreasures = new int[pathLength];

    cout << endl << "BOMB Placement" << endl;
    cout << "--------------" << endl;
    cout << "Enter the bomb positions in sets of 5 where a value" << endl;
    cout << "of 1=BOMB, and 0=NO BOMB. Space-delimit your input." << endl;
    cout << "(Example: 1 0 0 1 1) NOTE: there are " << pathLength << " to set!" << endl;

    for (int i = 0; i < (pathLength/Multiplier); i++) {
        cout << "   Positions [" << setw(2) << (i * Multiplier) + 1 << "-" << setw(2) << (i * Multiplier) + Multiplier << "]: ";

        for (int j = 0; j < Multiplier; j++) {
            cin >> pathBombs[i * Multiplier + j];
        }
    }

    cout << "BOMB placement set" << endl << endl;

    cout << "TREASURE Placement" << endl;
    cout << "------------------" << endl;
    cout << "Enter the treasure placements in sets of 5 where a value" << endl;
    cout << "of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input." << endl;
    cout << "(Example: 1 0 0 1 1) NOTE: there are " << pathLength << " to set!" << endl;

    for (int i = 0; i < (pathLength / Multiplier); i++) {
        cout << "   Positions [" << setw(2) << (i * Multiplier) + 1 << "-" << setw(2) << (i * Multiplier) + Multiplier << "]: ";

        for (int j = 0; j < Multiplier; j++) {
            cin >> pathTreasures[i * Multiplier + j];
        }
    }

    cout << "TREASURE placement set" << endl << endl;
}

void Game::printGameInfo() {
    cout << "Game:" << endl;
    cout << "   Path Length: " << pathLength << endl;
    cout << "   Bombs      : ";
    for (int i = 0; i < pathLength; i++) {
        cout << pathBombs[i];
    }
    cout << endl << "   Treasure   : ";
    for (int i = 0; i < pathLength; i++) {
        cout << pathTreasures[i];
    }
    cout << endl << endl;
}

void Game::playGame() {
    int nextMove;
    int result;

    printGameBoard();

    while (player.getLives() > 0 && maxMoves > 0) {
        cout << "Next Move [1-" << pathLength << "]: ";
        cin >> nextMove;

        if (nextMove < 1 || nextMove > pathLength) {
            cout << "Out of Range!!!" << endl;
            continue;
        }

        if (player.getPastPosition(nextMove)) {
            result = 1;
        }
        else {
            if (pathBombs[nextMove - 1] == 1 && pathTreasures[nextMove - 1] == 1) {
                result = 2;
                player.updatePlayerInfo(nextMove, result);
            }
            else if (pathBombs[nextMove - 1] == 1) {
                result = 3;
                player.updatePlayerInfo(nextMove, result);
            }
            else if (pathTreasures[nextMove - 1] == 1) {
                result = 4;
                player.updatePlayerInfo(nextMove, result);
            }
            else {
                result = 5;
                player.updatePlayerInfo(nextMove, result);
            }

            maxMoves--;
        }

        currentPlayerPosition = nextMove;

        printGameBoard();
    }

    if (player.getLives() == 0) {
        cout << "No more LIVES remaining!" << endl;
    }
}

void Game::printGameBoard() {

    int i;

    cout << "  ";
    for (i = 0; i <= pathLength; i++)
    {
        if (i == currentPlayerPosition - 1) {
            cout << player.getPlayerChar();
            break;
        }
        else {
           cout << " ";
        }
    }
    cout << endl;

    cout << "  ";
    for (i = 0; i < pathLength; i++) {
        if (i + 1 == currentPlayerPosition) {
            cout << player.getPlayerChar();
        }
        else if (player.getPastPosition(i + 1)) {
            if (pathBombs[i] == 1 && pathTreasures[i] == 1) {
                cout << "&";
            }
            else if (pathBombs[i] == 1) {
                cout << "!";
            }
            else if (pathTreasures[i] == 1) {
                cout << "$";
            }
            else {
                cout << ".";
            }
        }
        else {
            cout << "-";
        }
    }
    cout << endl;

    cout << "  ";
    for (i = 1; i <= pathLength; i++)
    {
        if (i % 10 == 0) {
            cout << (i / 10);
        }
        else {
           cout << "|";
        }
    }
    cout << endl;

    cout << "  ";
    for (i = 1; i <= pathLength; i++)
    {
        cout << (i % 10);
    }
    cout << endl << endl;

    cout << "+---------------------------------------------------+" << endl;
    cout << "  Lives: " << player.getLives() << " | Treasures: " << player.getTreasuresNo() << " | Moves Remaining : " << maxMoves << endl;
    cout << "+---------------------------------------------------+" << endl << endl;
}