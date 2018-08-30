#ifndef RPGSFML_MUSIC
#define RPGSFML_MUSIC

#include <SFML/Audio.hpp>

class Music {
    sf::Music mainTheme;
    sf::Music shotSound;
    sf::Music coinSound;
    sf::Music echoSlamSound;
    sf::Music collisionSound;
    sf::Music die;
public:
    Music();
    sf::Music& getMainTheme();
    sf::Music& getShotSound();
    sf::Music& getCoinSound();
    sf::Music& getEchoSlamSound();
    sf::Music& getCollisionSound();
    sf::Music& getDie();
};

#endif