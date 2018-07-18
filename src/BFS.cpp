//!
//! Created by armad on 5/24/2018.
//!

#include "BFS.h"
#include <bits/stdc++.h>
#include <limits.h>

/*
 * Shortest path in a maze algorithm
 * Basis for the algorithm was obtained from a free educational website "https://!www.geeksforgeeks.org"
 * And the link for this specific algorithm can be found here:
 * The article is written by Aditya Goel
 * I have modified this algorithm to fit the needs of this program.
 */

BFS::BFS(int h, int w) {
    height = h;
    width = w;
}
bool BFS::isValid(MapObjects*** &theMAP, int row, int col)
{
    //! check if row number and column number is in range
    return (row >= 0) && (col >= 0) && (row < height) && (col < width) && theMAP[row][col]->isEmpty();
    //!                                    max height        max width
}

int BFS::getShortestDist(MapObjects*** &theMAP, Point src, Point dest) {

    //! An Data Structure for queue used in BFS
    struct queueNode
    {
        Point pt;  //! The cordinates of a cell
        int dist;  //! cell's distance of from the source
    };

//! These arrays are used to get row and column
//! numbers of 4 neighbours of a given cell
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    //!Source and destination must be accessible
    if (!theMAP[src.x][src.y]->isEmpty() || !theMAP[dest.x][dest.y]->isEmpty()) {
        return INT_MAX;
    }

	//!Make vector of same size as map, to know when a place is visited
	//!Not array because  ISO C++ forbids variable length array
	vector <vector <bool > >  visited (height, vector<bool> (width, false));

    //! Mark the source cell as visited
    visited[src.x][src.y] = true;

    //! Create a queue for BFS
    queue<queueNode> q;


    //! distance of source cell is 0
    queueNode s = {src, 0};
    q.push(s);  //! Enqueue source cell

    //! Do a BFS starting from source cell
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;

        //! If we have reached the destination cell,
        //! we are done
        if (pt.x == dest.x && pt.y == dest.y) {
            return curr.dist;
        }
        //! Otherwise dequeue the front cell in the queue
        //! and enqueue its adjacent cells
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            //! if adjacent cell is valid, has path and
            //! not visited yet, enqueue it.
            if (isValid(theMAP,row, col)  && !visited[row][col]) {
                //! mark cell as visited and enqueue it
                visited[row][col] = true;
                queueNode Adjcell = { {row, col}, curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }

    //!return -1 if destination cannot be reached
    return INT_MAX;
}

vector < Point > BFS::getShortestPath(MapObjects*** &theMAP, Point src, Point dest) {

    vector  < Point > path;
    vector  < Point > fail;
    //! A Data Structure for queue used in BFS
    struct queueNode
    {
        Point pt;  //! The cordinates of a cell
        int dist;  //! cell's distance of from the source
    };

//! These arrays are used to get row and column
//! numbers of 4 neighbours of a given cell
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    //!Source and destination must be accessible
    if (!theMAP[src.x][src.y]->isEmpty() || !theMAP[dest.x][dest.y]->isEmpty()) {
        return fail;
    }
	//!Make vector of same size as map, to know when a place is visited
	//!Not array because  ISO C++ forbids variable length array
	vector <vector <bool > >  visited (height, vector<bool> (width, false));
    //! Mark the source cell as visited
    visited[src.x][src.y] = true;

    //! Create a queue for BFS
    queue<queueNode> q;


    //! distance of source cell is 0
    queueNode s = {src, 0};
    q.push(s);  //! Enqueue source cell

    //! Do a BFS starting from source cell
    Point pathPT = src;
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;
        //!Get coordinates of the next step that is closer to the destination but is also
        //!not more than one step away from the current coordinate
        if( (getShortestDist(theMAP, curr.pt, dest) < (getShortestDist(theMAP, pathPT, dest)) &&
                ( (( abs(pt.x - pathPT.x) == 1 ) && (abs(pt.y - pathPT.y) == 0)) ) )||
                ( (( abs(pt.x - pathPT.x) == 0 ) && (abs(pt.y - pathPT.y) == 1)) ) ) {
            pathPT = curr.pt;
            path.push_back(curr.pt);
        }

        //! If we have reached the destination cell,
        //! we are done
        if (pt.x == dest.x && pt.y == dest.y) {
            return path;
        }
        //! Otherwise dequeue the front cell in the queue
        //! and enqueue its adjacent cells
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            //! if adjacent cell is valid, has path and
            //! not visited yet, enqueue it.
            if (isValid(theMAP,row, col)  && !visited[row][col]) {
                //! mark cell as visited and enqueue it
                visited[row][col] = true;
                queueNode Adjcell = { {row, col}, curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }

    //!return -1 if destination cannot be reached

    return fail;
}
