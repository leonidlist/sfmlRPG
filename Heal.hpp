#pragma once
#include "Entity.hpp"

class Heal:public Entity {
public:
    bool destroy = false;
    bool isShop = false;
    bool isOnCoolDown = false;
    int coolDownDuration = 5;
    int price = 50;

    Heal(sf::Texture &texture, int x, int y, sf::Font &font);
    void update();
};