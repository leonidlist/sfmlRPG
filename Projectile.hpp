#ifndef RPGSFML_PROJECTILE_H
#define RPGSFML_PROJECTILE_H

#include "Entity.hpp"

class Projectile:public Entity {
public:
    int movementSpeed = 10;
    int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right

    int attackDamage = 5;
    bool destroy = false;
    int lifeTime = 15;
    int lifeCounter = 0;
    int animationCounter = 0;

    bool enemyProjectile = false;

    Projectile();
    void update();
};

#endif
