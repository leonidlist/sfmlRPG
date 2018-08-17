#ifndef RPGSFML_ENTITY_H
#define RPGSFML_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

class Entity {
public:
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
};

#endif
