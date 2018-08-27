#include "Projectile.hpp"

Projectile::Projectile() {
    rect.setSize(sf::Vector2f(15, 15));
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::Black);
}

void Projectile::update() {
    switch(direction) {
        case 1: //Up
            rect.move(0,-movementSpeed);
            sprite.setTextureRect(sf::IntRect(animationCounter*32,3*32,32,32));
            sprite.setPosition(rect.getPosition());
            break;
        case 2: //Down
            rect.move(0,movementSpeed);
            sprite.setTextureRect(sf::IntRect(animationCounter*32,0*32,32,32));
            sprite.setPosition(rect.getPosition());
            break;
        case 3: //Left
            rect.move(-movementSpeed,0);
            sprite.setTextureRect(sf::IntRect(animationCounter*32,1*32,32,32));
            sprite.setPosition(rect.getPosition());
            break;
        case 4: //Right
            rect.move(movementSpeed, 0);
            sprite.setTextureRect(sf::IntRect(animationCounter*32,2*32,32,32));
            sprite.setPosition(rect.getPosition());
            break;
    }

    animationCounter++;
    if(animationCounter > 2) {
        animationCounter = 0;
    }
    lifeCounter++;
    if(lifeCounter >= lifeTime) {
        destroy = true;
    }
}