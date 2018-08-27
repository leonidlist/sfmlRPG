#include "TextDisplay.hpp"

TextDisplay::TextDisplay() {}

void TextDisplay::update() {
    text.move(0,-movementSpeed);

    lifeTime++;
    if(lifeTime >= lifeTimeCounter) {
        destroy = true;
    }
}