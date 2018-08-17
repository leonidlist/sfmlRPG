#ifndef RPGSFML_PICKUP
#define RPGSFML_PICKUP

#include "Entity.h"

class Pickup:public Entity {
public:
    bool isCoin = true;
    float animationCounter = 0;
    bool destroy = false;

    Pickup();
    void update();
};

#endif