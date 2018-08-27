#ifndef RPGSFML_MUSIC
#define RPGSFML_MUSIC

#include <SFML/Audio.hpp>

class Music {
    sf::Music mainTheme;
    sf::Music shotSound;
    sf::Music coinSound;
    sf::Music echoSlamSound;
    sf::Music collisionSound;
public:
    Music();
    sf::Music& getMainTheme();
    sf::Music& getShotSound();
    sf::Music& getCoinSound();
    sf::Music& getEchoSlamSound();
    sf::Music& getCollisionSound();
};

#endif