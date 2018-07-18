//!
//! Created by armad on 5/21/2018.
//!

#include "Tower.h"

Tower::Tower(int dmg, int rng, int cst) {
    damage = dmg;
    range = rng;
    cost = cst;
}

int Tower::getDamag() {
    return damage;
}

int Tower::getRange() {
    return range;
}
int Tower::upgradeDamage() {
    damage *= 1.3;
return damage;
}
int Tower::upgradeRange() {
    range *= 1.3;
return range;
}
int Tower::changeDamage(int dam) {
    damage = dam;
return damage;
}
int Tower::changeRange(int rang) {
    range = rang;
return range;
}
bool Tower::isTower() const {
    return true;
}
bool Tower::isEmpty() const {
    return true;
}