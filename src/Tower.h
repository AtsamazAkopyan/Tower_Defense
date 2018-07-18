//!
//! Created by armad on 5/21/2018.
//!

#ifndef PA2PROJECT_TOWER_H
#define PA2PROJECT_TOWER_H
#include "FileReaderClass.h"
#include "MapObjects/MapObjects.h"

class Tower : public MapObjects {
public:
    bool isTower () const override;
    bool isEmpty () const override;


    Tower(int dmg = 0, int rng = 0, int cst = 0);

    int getDamag();
    int getRange();
    int getCost();

    int upgradeRange();
    int upgradeDamage();

    int changeRange(int rang);
    int changeDamage(int dam);

protected:
    int damage;
    int range;
    int cost;
};


#endif //!PA2PROJECT_TOWER_H
