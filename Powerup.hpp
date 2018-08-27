#ifndef RPGSFML_POWERUP
#define RPGSFML_POWERUP

#include "Entity.hpp"

class Powerup:public Entity {
public:
    bool destroy = false;
    float animationCounter = 0;

    Powerup();
    void update();
};

#endif