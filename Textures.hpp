#ifndef RPGSFML_TEXTURES
#define RPGSFML_TEXTURES

#include <SFML/Graphics.hpp>

class Textures {
    sf::Texture textureCharacter;
    sf::Texture enemyTexture;
    sf::Texture fireballTexture;
    sf::Texture coinTexture;
    sf::Texture powerupTexture;
    sf::Texture healTexture;
    sf::Texture wallTexture;
    sf::Texture boxTexture;
    sf::Texture echoSlamTexture;
    sf::Texture tileTexture;

    public:
    Textures();

    sf::Texture& getTextureCharacter();
    sf::Texture& getEnemyTexture();
    sf::Texture& getFireballTexture();
    sf::Texture& getCoinTexture();
    sf::Texture& getPowerupTexture();
    sf::Texture& getHealTexture();
    sf::Texture& getWallTexture();
    sf::Texture& getBoxTexture();
    sf::Texture& getEchoSlamTexture();
    sf::Texture& getTileTexture();
};

#endif