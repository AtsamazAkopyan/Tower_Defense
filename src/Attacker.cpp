//!
//! Created by armad on 5/21/2018.
//!

#include "Attacker.h"

Attacker::Attacker(int hp, int spd) {
    health = hp;
    speed = spd;
}

int Attacker::getHealth() {
    return health;
}

int Attacker::getSpeed() {
    return speed;
}
void Attacker::boostHealth() {
    health *= 1.5;
}
void Attacker::changeHealth(int newHealth) {
    health = newHealth;
}
