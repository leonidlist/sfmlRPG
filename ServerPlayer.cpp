#include "ServerPlayer.hpp"

void ServerPlayer::setPlayerPosition(sf::Vector2f obj) {
    this->playerPosition = obj;
}

void ServerPlayer::setUniqueID(int data) {
    this->uniqueID = data;
}

sf::Vector2f ServerPlayer::getPlayerPosition() {
    return this->playerPosition;
}

int ServerPlayer::getUniqueID() {
    return this->uniqueID;
}