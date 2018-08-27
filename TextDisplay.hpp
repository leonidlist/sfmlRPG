#ifndef RPGSFML_TEXT_DISPLAY
#define RPGSFML_TEXT_DISPLAY

#include "Entity.hpp"

class TextDisplay:public Entity {
public:
    std::string myString = "Default";
    float movementSpeed = 0.5;
    int lifeTime = 0;
    int lifeTimeCounter = 100;
    bool destroy = false;

    TextDisplay();
    void update();
};

#endif