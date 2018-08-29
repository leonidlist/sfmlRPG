#include "Enemy.hpp"

Enemy::Enemy(sf::Texture &texture, sf::Font &font) {
    rect.setSize(sf::Vector2f(32,32));
    rect.setPosition(350,350);
    rect.setFillColor(sf::Color::Cyan);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
    text.setFont(font);
    text.setPosition(rect.getPosition().x, (rect.getPosition().y-65));
    text.setCharacterSize(14);
    text.setColor(sf::Color::White);
    text.setString("HP: " + std::to_string(hp));
}

void Enemy::update() {
    sprite.setPosition(rect.getPosition());
    text.setString("HP: " + std::to_string(hp));
    text.setPosition(rect.getPosition());
}

void Enemy::updateMovement() {
    if(direction == 1 && canMoveUp) {
        rect.move(0,-movementSpeed);
        sprite.setTextureRect(sf::IntRect(counterWalking * 32,96,32,32));
        resetMoveLimits();
    }
    else if(direction == 2 && canMoveDown) {
        rect.move(0,movementSpeed);
        sprite.setTextureRect(sf::IntRect(counterWalking * 32,0,32,32));
        resetMoveLimits();
    }
    else if(direction == 3 && canMoveLeft) {
        rect.move(-movementSpeed, 0);
        sprite.setTextureRect(sf::IntRect(counterWalking * 32,32,32,32));
        resetMoveLimits();
    }
    else if(direction == 4 && canMoveRight) {
        rect.move(movementSpeed, 0);
        sprite.setTextureRect(sf::IntRect(counterWalking * 32,64,32,32));
        resetMoveLimits();
    }
    else {
        //Do not move!
    }
    counterWalking++;

    if(counterWalking > 2)
        counterWalking = 0;

    directionCoolDown++;

    if(directionCoolDown >= movementDuration && !isAggro) {
        direction = generateRandom(10);
        directionCoolDown = 0;
    }
}

void Enemy::resetMoveLimits() {
    canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}

void Enemy::spawnEnemies(int amount, Room &room, std::vector<Enemy> &arr, sf::Texture &texture, sf::Font &font) {
    Enemy enemy1(texture, font);
    for(int i = 0; i < amount; i++) {
        int randX = std::rand() % (room.endX-room.startX-140) + room.startX+70;
        int randY = std::rand() % (room.endY-room.startY-140) + room.startY+70;
        enemy1.rect.setPosition(randX, randY);
        arr.push_back(enemy1);
    }
}
