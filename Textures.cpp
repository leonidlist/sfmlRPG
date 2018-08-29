#include "Textures.hpp"

Textures::Textures() {
    if(!textureCharacter.loadFromFile("char.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!enemyTexture.loadFromFile("zombie.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!fireballTexture.loadFromFile("fireball.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!coinTexture.loadFromFile("Coins16x16.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!powerupTexture.loadFromFile("powerups.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!healTexture.loadFromFile("GemsAndHearts.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!wallTexture.loadFromFile("Back_002.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!boxTexture.loadFromFile("Crate_001.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!echoSlamTexture.loadFromFile("echoSlam.png"))
        throw std::runtime_error("Cannot load texture.");
    if(!tileTexture.loadFromFile("tile.png"))
        throw std::runtime_error("Cannot load texture.");
}

sf::Texture& Textures::getTextureCharacter() {
    return textureCharacter;
}

sf::Texture& Textures::getEnemyTexture() {
    return enemyTexture;
}

sf::Texture& Textures::getFireballTexture() {
    return fireballTexture;
}

sf::Texture& Textures::getCoinTexture() {
    return coinTexture;
}

sf::Texture& Textures::getPowerupTexture() {
    return powerupTexture;
}

sf::Texture& Textures::getHealTexture() {
    return healTexture;
}

sf::Texture& Textures::getWallTexture() {
    return wallTexture;
}

sf::Texture& Textures::getBoxTexture() {
    return boxTexture;
}

sf::Texture& Textures::getEchoSlamTexture() {
    return echoSlamTexture;
}