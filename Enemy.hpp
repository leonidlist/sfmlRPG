#ifndef RPGSFML_ENEMY_H
#define RPGSFML_ENEMY_H

#include "Entity.hpp"
#include "Random.hpp"
#include "Room.hpp"

class Enemy:public Entity {
public:
    int movementSpeed = 1;
    int movementDuration = 50;

    bool canMoveDown = true;
    bool canMoveUp = true;
    bool canMoveLeft = true;
    bool canMoveRight = true;

    int attackDamage = 3;

    int counterWalking = 0;
    int direction = 0;
    int directionCoolDown = 0;
    bool isAggro = false;

    int hp = 100;
    bool alive = true;

    Enemy(sf::Texture &texture, sf::Font &font);
    void update();
    void updateMovement();
    void resetMoveLimits();
    static void spawnEnemies(int amount, Room &room, std::vector<Enemy> &arr, sf::Texture &texture, sf::Font &font);
};

#endif
