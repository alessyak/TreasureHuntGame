#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
    livesNo = 0;
    playerChar = ' ';
    treasuresNo = 0;
    pastPositions = new int[MAX_Path] {0};
}

Player::~Player() {
    delete[] pastPositions;
}

void Player::configurePlayer() {
    cout << "PLAYER Configuration" << endl;
    cout << "--------------------" << endl;

    cout << "Enter a single character to represent the player: ";
    cin >> playerChar;

    do {
        cout << "Set the number of lives (1-10): ";
        cin >> livesNo;

        if (livesNo == 0 || livesNo > MAX_Lives)
            cout << "Must be between 1 and 10!" << endl;

    } while (!(livesNo > 0 && livesNo <= MAX_Lives));

    pastPositions = new int[MAX_Path] {0};
}

void Player::printPlayerInfo() {
    cout << "Player:\n";
    cout << "   Symbol     : " << playerChar << endl;
    cout << "   Lives      : " << livesNo << endl;
    cout << "   Treasure   : " << "[ready for gameplay]" << endl;
    cout << "   History    : " << "[ready for gameplay]" << endl;
}

void Player::updatePlayerInfo(int nextMove, int result) {
    pastPositions[nextMove - 1] = 1;

    if (result == 1) {
        cout << endl << "===============> Dope! You've been here before!" << endl << endl;
    }
    else if (result == 2) {
        cout << endl << "===============> [&] !!! BOOOOOM !!! [&]" << endl;
        cout << "===============> [&] $$$ Life Insurance Payout!!! [&]" << endl << endl;
        livesNo--;
        treasuresNo++;
    }
    else if (result == 3) {
        cout << endl << "===============> [!] !!! BOOOOOM !!! [!]" << endl << endl;
        livesNo--;
    }
    else if (result == 4) {
        cout << endl << "===============> [$] $$$ Found Treasure! $$$ [$]" << endl << endl;
        treasuresNo++;
    }
    else if (result == 5) {
        cout << endl << "===============> [.] ...Nothing found here... [.]" << endl << endl;
    }
}

int Player::getLives()const {
    return livesNo;
}

char Player::getPlayerChar()const {
    return playerChar;
}

bool Player::getPastPosition(int position) const {
    return position >= 1 && position <= MAX_Path && pastPositions[position - 1] == 1;
}

int Player::getTreasuresNo()const {
    return treasuresNo;
}