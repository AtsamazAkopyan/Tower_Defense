//!
//! Created by armad on 5/21/2018.
//!

#ifndef PA2PROJECT_ATTACKER_H
#define PA2PROJECT_ATTACKER_H

//! Attacker has health and speed.
class Attacker {
public:
    Attacker(int hp, int spd);
    int getSpeed();
    int getHealth();
    void boostHealth();
    void changeHealth(int newHealth);
protected:
    unsigned int health;
    unsigned int speed;
};


#endif //!PA2PROJECT_ATTACKER_H
