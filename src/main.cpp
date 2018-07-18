#include <iostream>
#include <vector>
#include "Tower.h"
#include "Attacker.h"
#include "Map.h"
#include "BFS.h"
#include "gameLoop.h"
#include <thread>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <limits.h>

/*
 * A TOWER DEFENSE GAME FOR "PROGRAMMING AND ALGORITHMS 2" CLASS BY ATSAMAZ AKOPYAN.
 * THIS GAME IS PLAYED FROM THE TERMINAL AND IT IS RECOMMENDED NOT TO PLAY VIA AN IDE
 * BECAUSE IDE's MAY AFFECT THE PRINTING OF THE GAME. IF YOU ARE USING AN IDE SUCH AS
 * CLION, PLEASE USE THE DEBUGGER.
 *
 * FILES ARE READ BY THE "FileReaderClass.h" CLASS.
 * SHORTEST PATH ALGORITHM IS BFS in BFS.h CLASS.
 * AFTER EVERY PRINT OF THE MAP, SYS CLEAR AND FLUSH IS CALLED TO CLEAN THE TERMINAL FOR NEXT PRINT.
*/

using namespace std;
//!Starting values can easily be edited here.

int main() {

    //!Vector in which the textual map from file will be stored in.
    vector<char> vectorMap;
	FileReaderClass readingFile;
    vectorMap = readingFile.charMap(vectorMap);
    if(vectorMap.empty()){
        cout <<"Error! Map file either bad or empty!" << endl;
        //!system("pause"); Only on windows
        return 0;
    }
    //!Initializing object of class "Map" to height and width values from file
    Map myMapObject(readingFile.getHeight(),readingFile.getWidth());
    //!Creating a 2D Vector of objects from 1D vector of characters
    if(myMapObject.makeMap(vectorMap) == -1){
        return 0;
    }


    //!Vector to store path coordinates.
    //!Therefore the vector is of type struct Point.
    vector < Point > path;

    //!Initializing BFS lower values of high and width because of the 0th position
    BFS pathObject(readingFile.getHeight()-1,readingFile.getWidth()-1);
    //!Doing a BFS to check whether a path exists
    int distance = pathObject.getShortestDist(myMapObject.theMAP, myMapObject.src, myMapObject.dest);
    if(distance == INT_MAX){
        cout <<"Error! Cant get distance" << endl;
        //!system("pause"); Only on windows
        return 0;
    }else {
        cout << "Path took " << distance << " steps." << endl;
    }
    //!Obtaining a path from the BFS algorithm class.
    path = pathObject.getShortestPath(myMapObject.theMAP, myMapObject.src, myMapObject.dest);
    if(path.empty()){
        cout <<"Error! Cant get path" << endl;
        //!system("pause"); Only on windows
        return 0;
    }
	cout << "Path size: " << path.size() << endl;
    //!Putting path objects into the 2D map
    //!instead of basic MapObjects objects
    myMapObject.addPathToMap(path);

    //!Reading monster and tower stats from files
    vector<int> stats;
    if(readingFile.monsterStats(stats) == -1){
        cout <<"Error! Monster stats file is empty!" << endl;
        //!system("pause"); Only on windows
        return 0;
    }
    Attacker attacker(stats[0], stats[1]);
    stats.clear();
    if(readingFile.towerStats(stats) == -1){
        cout <<"Error! Tower stats file is empty!" << endl;
        //!system("pause"); Only on windows
        return 0;
    }
    Tower Atower(stats[0], stats[1],stats[2]);

    //!Creating object of gameLoop
    gameLoop GAME;

    //!Ask user if they would like to load a previous game
    cout << "Would you like to load a previous game?\n"
            "Type '1' for Yes\n"
            "Type '2' for No\n" << endl;
    int loadGameSwitchCase;
    while ( !( cin >> loadGameSwitchCase) || loadGameSwitchCase < 1 || loadGameSwitchCase > 2) { //! invalid input
        if (feof(stdin)) { //!Check for EOF
            return 0;
        }
        cin . clear ();                 //! clear the fail bit
        cin . ignore ( INT_MAX, '\n' ); //! discard the input (the invalid characters), until the end-of-line
        cout << "Invalid input. Please enter integers! Either a '1' or '2'" << endl;
    }
    //!Towers are stored in Vector of struct 'Point'
    //!which stores coordinates
    vector<Point> towerCoordinates;
    //!Check whether user made a choice
    bool userMadeChoice = false;
    //!Which level to load
    int startingRound = 1;
    while(!userMadeChoice)
    switch (loadGameSwitchCase){
        case 1 : {
            //!New int's to fetch data about a saved game from file
            int newTowerDamage;
            int newTowerRange;
            int newAttackedHealth;
            if(readingFile.loadGame(towerCoordinates, newTowerRange ,newTowerDamage,
                       newAttackedHealth ,startingRound, GAME.numberOfTowers, GAME.credits) == -1){
                cout <<"Error! Saved game file is bad or empty!" << endl;
                //!system("pause"); Only on windows
                return 0;
            }
            for (unsigned int j = 0; j < towerCoordinates.size(); ++j) {
                if(!myMapObject.theMAP[towerCoordinates[j].x][towerCoordinates[j].y]->isEmpty() ||
                   myMapObject.theMAP[towerCoordinates[j].x][towerCoordinates[j].y]->isPath()){
                    cout <<"Tower in invalid position!" << endl;
                    return 0;
                }
            }
            //!Changing stats to stats from saved file
            Atower.changeRange(newTowerRange);
            Atower.changeDamage(newTowerDamage);
            attacker.changeHealth(newAttackedHealth);
            //!Replace previous objects with loaded towers
            for (unsigned int i = 0; i < towerCoordinates.size(); ++i) {
                delete myMapObject.theMAP[towerCoordinates[i].x][towerCoordinates[i].y];
                myMapObject.theMAP[towerCoordinates[i].x][towerCoordinates[i].y] = new Tower;
            }
            GAME.credits -= 100; //!Balance as loaded game starts on previous round
            userMadeChoice = true;
            break;
        }
        case 2 : {
            //!Make user add their first Tower;
            towerCoordinates.push_back(GAME.addTower(myMapObject));
            if(towerCoordinates[towerCoordinates.size()-1].x == -1){
                return 0;
            }
            GAME.numberOfTowers++;
            userMadeChoice = true;
            break;
        }
        default: {
            cout << "Please type either '1' or '2' " << endl;
            userMadeChoice = false;
            break;
        }
    }


    for (GAME.gameRound = startingRound; GAME.gameRound < 20; ++GAME.gameRound) {
        int check = 0;
        //!gameLoop returns 0 if loss
        check = GAME.gameLoops(path, myMapObject, towerCoordinates, Atower, attacker, pathObject, GAME.gameRound, readingFile);
        if(check == 0) {
           cout << "You lost!" << endl;
           //!system("pause");//! Only on windows
           return 0;
        }
        if(check == -1){
           return 0;
         }
        //!Increasing attackers health for higher difficulty next rounds
        attacker.boostHealth();
    }

    return 0;
}
