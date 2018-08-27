#include "Wall.hpp"

Wall::Wall() {
    rect.setSize(sf::Vector2f(props,props));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(0,0);
}

int Wall::props = 70;

int Wall::getProps() {
    return props;
}