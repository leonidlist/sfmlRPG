#include "Player.hpp"

Player::Player() {
    rect.setSize(sf::Vector2f(30,51));
    rect.setPosition(150, 10*80);
    rect.setFillColor(sf::Color::Cyan);
    sprite.setTextureRect(sf::IntRect(0,0,30,51));
}

void Player::update() {
    sprite.setPosition(rect.getPosition());
}

void Player::updateMovement() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        movementSpeed += 2;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canMoveUp) {
        direction = 1;
        if(counterWalking > 2)
            counterWalking = 0;
        sprite.setTextureRect(sf::IntRect((int)counterWalking * 30,0,30,51));
        rect.move(0,-movementSpeed);
        counterWalking+=0.5;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && canMoveDown) {
        direction = 2;
        if(counterWalking > 2)
            counterWalking = 0;
        sprite.setTextureRect(sf::IntRect((int)counterWalking * 30,102,30,51));
        rect.move(0,movementSpeed);
        counterWalking+=0.5;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && canMoveLeft) {
        direction = 3;
        if(counterWalking > 2)
            counterWalking = 0;
        sprite.setTextureRect(sf::IntRect((int)counterWalking * 30,155,30,51));
        rect.move(-movementSpeed, 0);
        counterWalking+=0.5;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && canMoveRight) {
        direction = 4;
        if(counterWalking > 2)
            counterWalking = 0;
        sprite.setTextureRect(sf::IntRect((int)counterWalking * 30,51,30,51));
        rect.move(movementSpeed,0);
        counterWalking+=0.5;
    }
    movementSpeed = 2;
}

void Player::resetMoveLimits() {
    canMoveDown = canMoveUp = canMoveLeft = canMoveRight = true;
}

void Player::updateView(sf::View &v) {
    v.setCenter(sf::Vector2f(rect.getPosition().x, rect.getPosition().y));
}