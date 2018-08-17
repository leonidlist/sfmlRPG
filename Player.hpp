#ifndef RPGSFML_PLAYER_H
#define RPGSFML_PLAYER_H

#include "Entity.hpp"

class Player:public Entity {
public:
    int uniqueID;

    int movementSpeed = 3;
    int counterWalking = 0;
    int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right
    bool canMoveUp = true;
    bool canMoveDown = true;
    bool canMoveLeft = true;
    bool canMoveRight = true;

    int attackDamage = 25;
    int powerupLevel = 0;

    int hp = 100;
    int money = 0;

    Player();
    void update();
    void updateMovement();
    void resetMoveLimits();
    void updateView(sf::View &v);

};

#endif //RPGSFML_PLAYER_H
