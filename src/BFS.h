//!
//! Created by armad on 5/24/2018.
//!

#ifndef PA2PROJECT_BFS_H
#define PA2PROJECT_BFS_H
#include "Map.h"
#include <stack>

class BFS {
public:

    BFS(int h, int w);

    //!To check if a given point on the map is empty and the point exists.
    bool isValid(MapObjects*** &theMAP, int row, int col);

    //!For towers to get shortest distance to monsters.
    int getShortestDist(MapObjects*** &theMAP, Point src, Point dest);

    //!For monsters to get a path from entrance to exit.
    std::vector < Point > getShortestPath(MapObjects*** &theMAP, Point src, Point dest);

protected:
    int height = 0;
    int width = 0;
};


#endif //!PA2PROJECT_BFS_H
