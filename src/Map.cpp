//!
//! Created by armad on 5/22/2018.
//!

#include "Map.h"
#include <vector>
using namespace std;

Map::Map(unsigned int h, unsigned int w){
    height = h;
    width = w;
}
int Map::makeMap(const vector <char> &vectorMap) {
    //!2D vector of pointers to different objects that all inherit from MapObjects
    //!or are an object of that class
    theMAP = new MapObjects**[height];
    for (unsigned int i = 0; i < height; i++) {
        theMAP[i] = new MapObjects*[width];
    }

    int iterator = 0;
    int determineStartEnd = 0;
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j, iterator++) {
            cout << vectorMap[iterator];

            //! '#' is not empty and is a wall
            if(vectorMap[iterator] == '#')
                theMAP[i][j] = new Wall();
            //! '=' considered as empty
            if(vectorMap[iterator] == ' ' || vectorMap[iterator] == '=')
                theMAP[i][j] = new MapObjects();
            //! First time we meet '<' its the start and second time we encounter it its the end
            if(vectorMap[iterator] == '>') {

                if (determineStartEnd == 0) {
                    theMAP[i][j] = new MapObjects();
                    src.y = j;
                    src.x = i;
                    determineStartEnd++;
                } else {
                    theMAP[i][j] = new MapObjects();
                    dest.y = j;
                    dest.x = i;
                    determineStartEnd++;
                }
            }
        }
        cout << endl;
    }
    if(determineStartEnd != 2){
        cout << "Must have one Exit and one Entrance '<'!!" << endl;
        return -1;
    }
    return 0;
}
void Map::addPathToMap(const vector <Point> &path){
    //!Delete some objects of MapObject which are considered as empty
    //!and replace them with the objects of class path
    for (unsigned int i = 0; i < path.size(); ++i) {
        delete theMAP[path[i].x][path[i].y];
        theMAP[path[i].x][path[i].y] =  new Path;
    }
}

Map::~Map() {
    //!Delete all objects in the 2D vector
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            delete theMAP[i][j];
        }
        delete[] theMAP[i];
    }
    delete[] theMAP;
    theMAP = NULL;
}

