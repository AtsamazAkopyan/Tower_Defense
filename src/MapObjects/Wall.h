//!
//! Created by armad on 5/22/2018.
//!

#ifndef PA2PROJECT_WALL_H
#define PA2PROJECT_WALL_H
#include "MapObjects.h"


class Wall : public MapObjects {
public:
    bool isEmpty () const override;
};


#endif //!PA2PROJECT_WALL_H
