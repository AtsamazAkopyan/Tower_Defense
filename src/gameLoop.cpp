//!
//! Created by armad on 6/7/2018.
//!
#include "gameLoop.h"
#include <thread>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <limits.h>
#include <vector>
#include <iostream>


int gameLoop::gameLoops(vector <Point> path, Map &myMapObject, vector <Point> &towerCoordinates,
             Tower &Atower, Attacker &attacker, BFS &pathObject, int round, FileReaderClass &readingFile){
    bool game = true;
    int healthAttacker = attacker.getHealth();
    while(game) {

        clock_t loopTime; //! Starting to time the loop.
        loopTime = clock();


        //!system ("CLS");//!For Windows
        cout <<flush; //! Clearing the terminal for the next print.
        //!system ("CLS");
        cout << "\033[H\033[2J";//!This is for Linux terminal

        //!Check if monster moved so it is only printed once
        cout << "Round: " << round << endl;
        bool monsterMoved = false;
        Point monsterPosition {0,0};
        for (unsigned int i = 0; i < readingFile.getHeight(); ++i) {
            for (unsigned int j = 0; j < readingFile.getWidth(); ++j) {

                //!If a position on map is a tower, then print it
                if(myMapObject.theMAP[i][j]->isTower()){
                    cout << "A";
                    continue;
                }
                //!If a position on the map is attacker, then print it
                if(i == (unsigned int)path[0].x && j == (unsigned int)path[0].y && !monsterMoved ) {
                    cout << "%";
                    monsterPosition.y = j;
                    monsterPosition.x = i;
                    path.erase(path.begin());
                    monsterMoved = true;
                    continue;
                }
                //!Print empty objects as space
                //!Print wall as #
                //!Print entrance and exit as >
                if(myMapObject.theMAP[i][j]->isEmpty()){
                    if( (unsigned int)myMapObject.src.x == i && (unsigned int)myMapObject.src.y == j){
                        cout << ">";
                    }
                    else if( (unsigned int) myMapObject.dest.x == i && (unsigned int) myMapObject.dest.y == j){
                        cout << " >";
                    }
                    else {
                        cout << " ";
                    }
                }
                if(!myMapObject.theMAP[i][j]->isEmpty()) {
                    cout << "#";
                }
            }
            cout << endl;
        }
        if(path.empty()){
            //!If vector path has no more elements, then the attacker has walked to the exit
            return 0;
        }
        for (unsigned int iteration = 0; iteration < towerCoordinates.size(); ++iteration) {
            //!If distance from tower to attacker is < or = to 10, tower can damage the attacker
            if(pathObject.getShortestDist(myMapObject.theMAP, towerCoordinates[iteration], monsterPosition) <= Atower.getRange()){
                healthAttacker -=  Atower.getDamag();
                //!If attacker's health is below 0, round is won
                if(healthAttacker <= 0){
                    game = false;
                    cout << "You won!!" << endl;
                    //!system("pause"); Only on windows
                    if(round < totalRounds - 1) {
                        if(roundWon(towerCoordinates, myMapObject, Atower, readingFile, attacker) == -1){
                            return -1;
                        }
                    }
                    break;
                }
            }
        }
        //!Printing remaining health of the attacker at the bottom of the map
        //!on each iteration
        if( healthAttacker > 0 ){
            cout << "Remaining health: " << healthAttacker << endl;
        }
        //!Total time elapsed since start of game while loop
        clock_t totalTime;
        for (;;) {
            totalTime = clock() - loopTime;
            //! Making sure that every loop iteration last one second.
            if ((((float) totalTime) / CLOCKS_PER_SEC) > 0.5) {
                //!                                   One ^ second
                //!If 1 second passed, break loop.
                break;
            }
        }
    }
    return 1;
}

int gameLoop::roundWon (vector<Point> &towerCoordinates, Map &myMapObject, Tower &Atower,
              FileReaderClass &readingFile, Attacker &attacker){
    //!Award user 100 credits at a win of every round
    credits += 100;
    cout << "Round 1 Complete! +100 CREDITS!\n"
            "Current Credit Balance: " << credits << endl;
    //!If user decided on move strategy
    int userMadeChoice = false;

    while(!userMadeChoice) {
        int switchCase1 = 0;
        int switchCase2 = 0;
        cout << "(1) To buy another tower, type '1'. COST " << 100*numberOfTowers <<"\n"
                                                                                    "(2) To upgrade existing towers, type '2'. COST "<< 50*numberOfTowerUpgrades <<"\n"
                                                                                                                                                                   "(3) To do nothing, type '3'\n"
                                                                                                                                                                   "(4) To save game type 4" << endl;
        while ( ! ( cin >> switchCase1) ) { //! invalid input
            if (feof(stdin)) { //!Check for EOF
                return -1;
            }
            cin . clear ();                 //! clear the fail bit
            cin . ignore ( INT_MAX, '\n' ); //! discard the input (the invalid characters), until the end-of-line
            cout << "Invalid input. Please enter integers!" << endl;
        }
        //!First switch case with 4 options
        switch (switchCase1) {
            case 1 : {
                if(credits < 100 * numberOfTowers){
                    cout << "You don't have enough credits!" << endl;
                    userMadeChoice = false;
                    break;
                }
                cout << "You have selected 1" << endl;
                //!Get user to add a new tower

                towerCoordinates.push_back(addTower(myMapObject));
                if(towerCoordinates[towerCoordinates.size()-1].x == -1){
                    return -1;
                }
                //!Subtract cost of the tower(increases with more towers)
                credits -= 100 * numberOfTowers;
                //!Increase number of towers and break out of loop
                numberOfTowers++;
                userMadeChoice = true;
                break;
            }
            case 2 : {
                if(credits < 50 * numberOfTowerUpgrades){
                    cout << "You don't have enough credits!" << endl;
                    userMadeChoice = false;
                    break;
                }
                cout << "You have selected 2" << endl;
                cout << "Please specify what you would like upgraded.\n"
                        "Type '1' for Range  +30%\n"
                        "Type '2' for Damage +30%\n"
                        "Type something else to go back" << endl;
                while ( ! ( cin >> switchCase2) ) {  //! invalid input
                    if (feof(stdin)) { //!Check for EOF
                        return -1;
                    }
                    cin.clear();                 //! clear the fail bit
                    cin.ignore(INT_MAX, '\n'); //! discard the input (the invalid characters), until the end-of-line
                    cout << "Invalid input. Please enter integers!" << endl;
                }
                //!Second switch case with 2 options
                switch (switchCase2) {
                    case 1 : {
                        Atower.upgradeRange();
                        //!Subtract cost of the upgrades(increases with more upgrades)
                        credits -= 50 * numberOfTowerUpgrades;
                        //!Increase number of upgrades and break out of loop
                        numberOfTowerUpgrades++;
                        userMadeChoice = true;
                        break;
                    }
                    case 2 : {
                        Atower.upgradeDamage();
                        //!Subtract cost of the upgrades(increases with more upgrades)
                        credits -= 50 * numberOfTowerUpgrades;
                        numberOfTowerUpgrades++;
                        //!Increase number of upgrades and break out of loop
                        userMadeChoice = true;
                        break;
                    }
                    default: {
                        //!Take user back to choosing between adding a tower
                        //!or upgrading some part of tower
                        cout << "You chose to go back" << endl;
                        userMadeChoice = false;
                        break;
                    }
                }
                break;
            }
            case 3: {
                userMadeChoice = true;
                break;
            }
            case 4: {
                cout << "You have selected 4" << endl;
                ofstream outFileStream;
                outFileStream.open("savedGame.txt");
                if (outFileStream.fail()) {
                    outFileStream.close();
                    cout << "Error! Can't open save game file!" << endl;
                    //!system("pause"); Only on windows
                    return -1;
                }
                //!Write all tower coordinates
                outFileStream << numberOfTowers;
                outFileStream << "\n";
                for (unsigned int i = 0; i < towerCoordinates.size(); ++i) {
                    outFileStream << towerCoordinates[i].x;
                    outFileStream << "\n";
                    outFileStream << towerCoordinates[i].y;
                    outFileStream << "\n";
                }
                //!Break as in a newline "\n" is to make textFile readable whenever the user wants to
                //!load the game later otherwise no way to tell when an integer ends and another starts
                outFileStream << "\n";
                //!Write all stats that are modifiable by the game
                outFileStream << Atower.getRange();
                outFileStream << "\n";
                outFileStream << Atower.getDamag();
                outFileStream << "\n";
                outFileStream << attacker.getHealth();
                outFileStream << "\n";
                //!Write round number
                outFileStream << gameRound;
                outFileStream << "\n";
                outFileStream << credits;
                //!User did not make a choice of what to do for next round
                //!therefore, go back to the switch statement
                userMadeChoice = false;
                cout << "Game Saved!" << endl;
                break;
            }
            default: {
                //!If integer other than 1, 2 or 3 is detected
                cout << "Invalid input. Please enter either '1' or '2' or '3' or '4':" << endl;
                userMadeChoice = false;
                break;
            }
        }
    }
    return 0;
}
Point gameLoop::addTower (Map &myMapObject){
    cout << "Please enter coordinates where to place your Tower.\n"
            "Enter 'X Coordinate' 'Y Coordinate': ";
    int towerCoordinateY = 0,towerCoordinateX = 0;
    Point towerCoordinates {0,0};

    while ( ! ( cin >> towerCoordinateY >> towerCoordinateX)
            //! invalid input, i.e. coordinate outside of map range
            || (unsigned int)towerCoordinateY >= myMapObject.width
            || (unsigned int)towerCoordinateX >= myMapObject.height
            //! Check if tower can be placed at selected coordinates.
            || !myMapObject.theMAP[towerCoordinateX][towerCoordinateY]->isEmpty()
            ||  myMapObject.theMAP[towerCoordinateX][towerCoordinateY]->isPath()
            ||  myMapObject.theMAP[towerCoordinateX][towerCoordinateY]->isTower()) {

        if (feof(stdin)) { //!Check for EOF
            Point empty;
            empty.x = -1; empty.y = -1;
            return empty;
        }
        cin.clear();                 //! clear the fail bit
        cin.ignore(INT_MAX, '\n'); //! discard the input (the invalid characters), until the end-of-line
        cout << "Invalid input. Please enter valid coordinates:" << endl;
    }
    //!Set the struct Point to equal these coordiantes
    towerCoordinates.y = towerCoordinateY;
    towerCoordinates.x = towerCoordinateX;

    //!delete previously stored object and replace with type Building
    delete myMapObject.theMAP[towerCoordinates.x][towerCoordinates.y];
    myMapObject.theMAP[towerCoordinates.x][towerCoordinates.y] = new Tower;


    return towerCoordinates;
}


