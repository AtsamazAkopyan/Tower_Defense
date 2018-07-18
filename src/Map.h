//!
//! Created by armad on 5/22/2018.
//!

#ifndef PA2PROJECT_MAP_H
#define PA2PROJECT_MAP_H


#include "MapObjects/MapObjects.h"
#include "MapObjects/Wall.h"
#include "Tower.h"
#include "MapObjects/Path.h"
#include "FileReaderClass.h"
#include <cstdlib>


using namespace std;


//!to store map cell cordinates

using namespace std;
class Map {
public:
    unsigned int height = 0;
    unsigned int width = 0;
    Point src;
    Point dest;
    Map(unsigned  int h, unsigned int w);
    MapObjects*** theMAP;

    int makeMap(const vector <char> &vectorMap);
    void addPathToMap(const vector <Point> &path);

    ~Map();
};


#endif //!PA2PROJECT_MAP_H
