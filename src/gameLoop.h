//!
//! Created by armad on 6/7/2018.
//!
#include "Attacker.h"
#include "FileReaderClass.h"
#include "BFS.h"
#include "Tower.h"
#ifndef AKOPYATS_GAMELOOP_H
#define AKOPYATS_GAMELOOP_H


class gameLoop {
public:
int gameLoops(vector <Point> path, Map &myMapObject, vector <Point> &towerCoordinates,
         Tower &Atower, Attacker &attacker, BFS &pathObject, int round, FileReaderClass &readingFile);

int roundWon (vector<Point> &towerCoordinates, Map &myMapObject, Tower &Atower,
              FileReaderClass &readingFile, Attacker &attacker);
    //!gameLoop variables will constantly be modified so do not have to be protected
Point addTower (Map &myMapObject);
    int credits = 0;
    int numberOfTowers = 0;
    int numberOfTowerUpgrades = 0;
    int totalRounds = 20;
    int gameRound = 1;
};


#endif //!AKOPYATS_GAMELOOP_H
