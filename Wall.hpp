#ifndef RPGSFML_WALL
#define RPGSFML_WALL

#include "Entity.hpp"

class Wall:public Entity {
public:
    bool destructable = true;
    int hp = 180;
    static int props;

    Wall();
    static int getProps();
};

#endif