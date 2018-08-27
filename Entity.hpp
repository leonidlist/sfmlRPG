#ifndef RPGSFML_ENTITY_H
#define RPGSFML_ENTITY_H

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <tgmath.h>
#include <deque>
#include <list>
#include <vector>
#include <unistd.h>

class Entity {
public:
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
};

#endif
