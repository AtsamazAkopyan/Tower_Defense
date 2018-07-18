//!
//! Created by armad on 5/25/2018.
//!

#ifndef PA2PROJECT_PATH_H
#define PA2PROJECT_PATH_H
#include "MapObjects.h"

class Path : public MapObjects{
    bool isEmpty () const override;
    bool isPath () const override;
};


#endif //!PA2PROJECT_PATH_H
