//!
//! Created by armad on 5/22/2018.
//!

#include "FileReaderClass.h"
#include <iostream>
#include <fstream>

using namespace std;

unsigned int FileReaderClass::getHeight() {
    return  height;
}
unsigned int FileReaderClass::getWidth() {
    return width;
}
vector <char> FileReaderClass::charMap( vector <char> &charVector) {

    ifstream infilestream;
    string line_;
    infilestream.open("gameMap.txt");
    //!If file cannot be opened for some reason
    //!notify user that file is bad
    if (infilestream.fail()) {
        infilestream.close();
        charVector.clear();
        return charVector;
    }
    //!If first line is empty
    //!notify user that file is bad
    getline(infilestream, line_);
    if(line_.empty()){
        charVector.clear();
        infilestream.close();
        return charVector;
    }
    //!Set width and height to first 2 lines in the file respectively
    width = std::stoi( line_ );
    getline(infilestream, line_);
    height = std::stoi( line_ );

unsigned int iterator = 0;
    while(std::getline(infilestream, line_)) {
		line_.erase(line_.find_last_not_of(" \n\r\t")+1);


        //!Writing textual 2D map into 1D vector
        for (unsigned int i = 0; i < line_.size(); ++i) {
            charVector.push_back(line_[i]);
            //!If actual height is higher than said in file
            //!then file is invalid
            if(iterator == height) {
                //!Clear the vector and return an empty vector
                //!to indicate in main that something went wrong
                charVector.clear();
                infilestream.close();
                return charVector;
            }
            //!If actual width is smaller or higher than said in file
            //!then file is invalid
            if(line_.size() < width || line_.size() > width) {
                charVector.clear();
                infilestream.close();
                return charVector;
            }
        }

        //!Checking if all walls are present at the top
        //! and bottom as attacker has to travel from left
        //! side to the right side
        if(iterator == 0 || iterator == height-1){
            for (unsigned int i = 0; i < line_.size(); ++i) {
                //!No # at top of map
                if(line_[i] != '#') {
                    charVector.clear();
                    infilestream.close();
                    return charVector;
                }
            }
        }
        //!Iterates every while loop cycle
        //!shows the height of the map
        iterator++;
    }
    infilestream.close();

    return charVector;
}

int FileReaderClass::towerStats(vector <int> &towerStats) {
    string line_;
    ifstream infilestream;
    infilestream.open("towerStats.txt");
    if (infilestream.fail()) {
        infilestream.close();
        return -1;
    }
    //!Reading tower stats
    getline(infilestream, line_);
    if(line_.empty()){
        infilestream.close();
        return -1;
    }
    int damage = std::stoi( line_ );
    getline(infilestream, line_);
    int range = std::stoi( line_ );
    getline(infilestream, line_);
    int cost = std::stoi( line_ );

    //!Pushing tower stats into vector
    towerStats.push_back(damage);
    towerStats.push_back(range);
    towerStats.push_back(cost);

    infilestream.close();
return 0;

}
int FileReaderClass::monsterStats(vector <int> &monsterStats) {
    string line_;
    ifstream infilestream;
    infilestream.open("monsterStats.txt");
    if (infilestream.fail()) {
        infilestream.close();
        return -1;
    }
    //!Reading attacker stats
    getline(infilestream, line_);
    if(line_.empty()){
        infilestream.close();
        return -1;
    }
    int health = std::stoi( line_ );
    getline(infilestream, line_);
    int speed = std::stoi( line_ );

    //!Pushing tower stats into vector
    monsterStats.push_back(health);
    monsterStats.push_back(speed);

    infilestream.close();

return 0;

}
int FileReaderClass::loadGame( vector <Point> &towerCoordinates, int &towerRange, int &towerDamage,
                                    int &attackerHealth, int &gameRound, int &numberOfTowers, int &credits){
    string line_;
    ifstream infilestream;
    infilestream.open("savedGame.txt");
    if (infilestream.fail()) {
        infilestream.close();
        return -1;
    }
    //!First line contains number of towers
    getline(infilestream, line_);
    if(line_.empty()){
        infilestream.close();
        return -1;
    }
    numberOfTowers = std::stoi( line_ );

    for (int i = 0, j = 1; j < numberOfTowers*2; i+=2, j+=2) {
        Point coordinate;
        getline(infilestream, line_);
        coordinate.x = std::stoi(line_);
        if( (unsigned int)coordinate.x > height){
            infilestream.close();
            return -1;
        }
        getline(infilestream, line_);
        coordinate.y = std::stoi(line_);
        if( (unsigned int)coordinate.y > width){
            infilestream.close();
            return -1;
        }
        towerCoordinates.push_back(coordinate);
    } getline(infilestream, line_); //!Getting rid of empty line

    getline(infilestream, line_);
    towerRange = std::stoi( line_ );
    getline(infilestream, line_);
    towerDamage = std::stoi( line_ );
    getline(infilestream, line_);
    attackerHealth = std::stoi( line_ );
    getline(infilestream, line_);
    gameRound = std::stoi( line_ );
    getline(infilestream, line_);
    credits = std::stoi( line_ );

    infilestream.close();
    return 0;
}
