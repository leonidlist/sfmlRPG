#ifndef RPGSFML_FONTS
#define RPGSFML_FONTS

#include "SFML/include/Graphics/Font.hpp"

class Fonts {
    sf::Font textFont;
public:
    Fonts();
    sf::Font& getTextFont();
};

#endif