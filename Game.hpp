#ifndef SFMLRPG_GAME
#define SFMLRPG_GAME

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Fonts.hpp"
#include "Music.hpp"
#include "Textures.hpp"
#include "Vectors.hpp"

#include "Player.h"
#include "Powerup.h"
#include "Pickup.h"
#include "TextDisplay.h"
#include "Projectile.h"
    
class Game {
    Fonts gameFonts;
    Textures gameTextures;
    Music gameMusic;
    Vectors gameVectors;

    sf::RenderWindow window;

    Player player1;
    Player player2;

    Powerup powerup;
    Pickup coin;
    TextDisplay textDisplay;
    sf::Text moneyText;
    Projectile projectile;
    sf::Text hpText;
    sf::View view;
    sf::Sprite echoSlamSprite;
    sf::Text esCooldown;

public:
    Game(sf::VideoMode, std::string);

    sf::RenderWindow& getWindow();

    Fonts& getFonts();
    Textures& getTextures();
    Music& getMusic();
    Vectors& getVectors();

    Player& getPlayer1();
    Player& getPlayer2();
    Powerup& getPowerup();
    Pickup& getCoin();
    TextDisplay& getTextDisplay();
    sf::Text& getMoneyText();
    Heal& getHeal();
    Projectile& getProjectile();
    sf::Text& getHpText();
    sf::View& getView();
    sf::Sprite& getEchoSlamSprite();
    sf::Text& getEsCooldown();

    void generateLocation();

    void drawWalls();
    void drawPlayers();
    void drawProjectiles();
    void drawEnemies();
    void drawCoins();
    void drawPowerups();
    void drawHeals();
    void drawTexts();

    void playerWallCollision();
    void enemyWallCollision();
    void playerPickupCollision();
    void playerHealCollision(sf::Clock& coolDown);
    void playerPowerupCollision();
    void enemyProjectilePlayerCollision();
    void projectileEnemyCollision();
    void wallProjectileCollision();
    void enemyPlayerCollision(sf::Clock clock2, sf::Time elapsed);

    void resetLimits();
};

#endif