#include "Pickup.h"

Pickup::Pickup() {
    rect.setSize(sf::Vector2f(16,16));
    rect.setFillColor(sf::Color::Red);
    sprite.setTextureRect(sf::IntRect(0,16*6,16,16));
}

void Pickup::update() {
    sprite.setPosition(rect.getPosition());
    sprite.setTextureRect(sf::IntRect((int)animationCounter*16,16*6,16,16));
    animationCounter+=0.4;
    if(animationCounter > 4) {
        animationCounter = 0;
    }
}