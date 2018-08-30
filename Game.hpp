#ifndef SFMLRPG_GAME
#define SFMLRPG_GAME

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "Fonts.hpp"
#include "Music.hpp"
#include "Textures.hpp"
#include "Vectors.hpp"

#include "Player.hpp"
#include "Powerup.hpp"
#include "Pickup.hpp"
#include "TextDisplay.hpp"
#include "Projectile.hpp"
    
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
    void enemyPlayerCollision(sf::Clock& clock2, sf::Time& elapsed);

    void destroyPowerup();
    void destroyWall();
    void destroyCoin();
    void destroyText();
    void destroyEnemy();
    void destroyProjectile();

    void fire(sf::Clock& clock1, sf::Time& elapsed1, bool isFocused, sf::TcpSocket& skt);
    void aggro(sf::Clock& clock3, sf::Time& elapsed3);
    void checkEchoCastReady(sf::Clock& echoSlamCoolDown, bool isFocused);
    void echoSlamCast(sf::Clock& echoSlamCoolDown, bool isFocused);

    void textManipulations();

    void checkEnemyAmount();
    bool checkDeath();

    void resetLimits();
};

#endif