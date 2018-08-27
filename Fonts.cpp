#include "Fonts.hpp"

Fonts::Fonts() {
    if(!textFont.loadFromFile("sansation.ttf")) {
        throw std::runtime_error("Cannot load font.");
    }
}

sf::Font& Fonts::getTextFont() {
    return textFont;
}