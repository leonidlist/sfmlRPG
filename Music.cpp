#include "Music.hpp"

Music::Music() {
    if(!mainTheme.openFromFile("mainTheme2.wav")) {
        throw std::runtime_error("Cannot open audio.");
    }
    mainTheme.setVolume(10);
    mainTheme.setLoop(true);
    if(!shotSound.openFromFile("fireballSound.wav")) {
        throw std::runtime_error("Cannot open audio.");
    }
    shotSound.setVolume(30);
    shotSound.setPitch(3);
    if(!coinSound.openFromFile("coin.wav")) {
        throw std::runtime_error("Cannot open audio.");
    }
    coinSound.setVolume(50);
    if(!echoSlamSound.openFromFile("echoSlam.wav")) {
        throw std::runtime_error("Cannot open audio.");
    }
    echoSlamSound.setVolume(40);
    if(!collisionSound.openFromFile("collision.ogg")) {
        throw std::runtime_error("Cannot open audio.");
    }
    collisionSound.setVolume(60);
    if(!die.openFromFile("die.wav")) {
        throw std::runtime_error("Cannot open audio.");
    }
    die.setVolume(30);
    die.setLoop(true);
}

sf::Music& Music::getMainTheme() {
    return mainTheme;
}

sf::Music& Music::getShotSound() {
    return shotSound;
}

sf::Music& Music::getCoinSound() {
    return coinSound;    
}

sf::Music& Music::getEchoSlamSound() {
    return echoSlamSound;
}

sf::Music& Music::getCollisionSound() {
    return collisionSound;
}

sf::Music& Music::getDie() {
    return die;
}