#include "Powerup.hpp"

Powerup::Powerup() {
    rect.setSize(sf::Vector2f(32,32));
    rect.setPosition(0,0);
}

void Powerup::update() {
    sprite.setPosition(rect.getPosition());
    sprite.setTextureRect(sf::IntRect((int)animationCounter*32,32,32,32));
    animationCounter+=0.6;
    if(animationCounter >= 8)
        animationCounter = 0;
}