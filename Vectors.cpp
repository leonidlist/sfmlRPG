#include "Vectors.hpp"

Vectors::Vectors() {

}

std::vector<Powerup>& Vectors::getPowerupVector() {
    return powerupVector;
}

std::vector<Projectile>& Vectors::getProjectileVector() {
    return projectileVector;
}

std::vector<Enemy>& Vectors::getEnemyVector() {
    return enemyVector;
}

std::vector<Pickup>& Vectors::getPickupVector() {
    return pickupVector;
}

std::vector<Wall>& Vectors::getWallVector() {
    return wallVector;
}

std::vector<TextDisplay>& Vectors::getTextDisplayVector() {
    return textDisplayVector;    
}

std::vector<Heal>& Vectors::getHealVector() {
    return healVector;
}

std::vector<Room>& Vectors::getRoomVector() {
    return roomVector;
}