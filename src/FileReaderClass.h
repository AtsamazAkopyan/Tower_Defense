//!
//! Created by armad on 5/22/2018.
//!

#ifndef PA2PROJECT_FILEREADERCLASS_H
#define PA2PROJECT_FILEREADERCLASS_H
#include <vector>
#include <iostream>
struct Point
{
    int x;
    int y;
};

class FileReaderClass {
public:

    std::vector <char> charMap(std::vector <char> &vectorCharMap);
    int towerStats(std:: vector <int> &towerStats);
    int monsterStats(std:: vector <int> &monsterStats);
    int loadGame(std:: vector <Point> &towerCoordinates, int &towerRange, int &towerDamage,
                                   int &attackHealth, int &gameRound, int &numberOfTowers, int &credits);
    unsigned int getHeight();
    unsigned int getWidth();

protected:
    unsigned int height = 0;
    unsigned int width = 0;
};


#endif //!PA2PROJECT_FILEREADERCLASS_H
