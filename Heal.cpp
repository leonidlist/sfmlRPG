#include "Heal.hpp"

Heal::Heal(sf::Texture &texture, int x, int y, sf::Font &font) {
    rect.setSize(sf::Vector2f(16,16));
    rect.setPosition(x,y);
    sprite.setPosition(rect.getPosition());
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,16,16));
    text.setString("Price: " + std::to_string(price));
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(18);
    text.setPosition(rect.getPosition().x, rect.getPosition().y-25);
}

void Heal::update() {
    if(isOnCoolDown) {
        text.setString("Cooldown!");
        return;
    }
    text.setString("Price: " + std::to_string(price));
}