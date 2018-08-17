#ifndef RPGSFML_SERVER_PLAYER
#define RPGSFML_SERVER_PLAYER

#include <SFML/System.hpp>

class ServerPlayer {
    sf::Vector2f playerPosition;
    int uniqueID;
public:
    void setPlayerPosition(sf::Vector2f obj);
    void setUniqueID(int data);
    
    sf::Vector2f getPlayerPosition();
    int getUniqueID();
};

#endif