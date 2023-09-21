#ifndef PLAYER_H
#define PLAYER_H

#define MAX_Lives 10
#define MIN_Path 10
#define MAX_Path 70
#define Multiplier 5

class Player {
    int livesNo;
    char playerChar;
    int treasuresNo;
    int* pastPositions;
public:
    Player();
    virtual ~Player();
    void configurePlayer();
    void printPlayerInfo();
    void updatePlayerInfo(int nextMove, int result);
    int getLives()const;
    char getPlayerChar()const;
    bool getPastPosition(int position) const;
    int getTreasuresNo()const;
};

#endif