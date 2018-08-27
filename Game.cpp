#include "Game.hpp"

Game::Game(sf::VideoMode vm, std::string name):window(vm, name) {
    window.setFramerateLimit(60);

    player1.sprite.setTexture(gameTextures.getTextureCharacter());
    player1.rect.setPosition(300,300);
    player2.sprite.setTexture(gameTextures.getTextureCharacter());
    player2.rect.setPosition(300,300);

    powerup.sprite.setTexture(gameTextures.getPowerupTexture());
    powerup.rect.setPosition(420,420);
    gameVectors.getPowerupVector().push_back(powerup);

    Pickup coin;
    coin.sprite.setTexture(gameTextures.getCoinTexture());
    coin.rect.setPosition(500,500);
    gameVectors.getPickupVector().push_back(coin);
    coin.rect.setPosition(400,400);
    gameVectors.getPickupVector().push_back(coin);

    textDisplay.text.setPosition(player1.rect.getPosition().x + 16, player1.rect.getPosition().y - 16);
    textDisplay.text.setFont(gameFonts.getTextFont());
    textDisplay.text.setColor(sf::Color::Black);
    textDisplay.text.setCharacterSize(16);
    textDisplay.text.setString(std::to_string(player1.hp));
    gameVectors.getTextDisplayVector().push_back(textDisplay);

    moneyText.setCharacterSize(18);
    moneyText.setFont(gameFonts.getTextFont());
    moneyText.setColor(sf::Color::Black);
    moneyText.setPosition(window.getSize().x/2, 0);

    projectile.sprite.setTexture(gameTextures.getFireballTexture());

    hpText.setCharacterSize(18);
    hpText.setFont(gameFonts.getTextFont());
    hpText.setColor(sf::Color::Black);
    hpText.setPosition(window.getSize().x/2, 25);

    view.setSize(sf::Vector2f(window.getSize().x-100, window.getSize().y-100));
    view.setCenter(player1.rect.getPosition());
    window.setView(view);

    echoSlamSprite.setTexture(gameTextures.getEchoSlamTexture());

    esCooldown.setFont(gameFonts.getTextFont());
    esCooldown.setCharacterSize(16);
    esCooldown.setColor(sf::Color::Black);
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

void Game::generateLocation() {
    Room room1(0,0,8,8,2,3, gameVectors.getWallVector(), gameTextures.getWallTexture(), gameTextures.getBoxTexture());
    gameVectors.getRoomVector().push_back(room1);
    Enemy::spawnEnemies(6, room1, gameVectors.getEnemyVector(), gameTextures.getEnemyTexture(), gameFonts.getTextFont());
    Room room2(0-8*Wall::getProps(), 0+8*Wall::getProps(), 8, 8, 4, 4, gameVectors.getWallVector(), gameTextures.getWallTexture(), gameTextures.getBoxTexture());
    gameVectors.getRoomVector().push_back(room2);
    Enemy::spawnEnemies(6, room2, gameVectors.getEnemyVector(), gameTextures.getEnemyTexture(), gameFonts.getTextFont());
    Room room3(0+8*Wall::getProps(), 0+8*Wall::getProps(), 8, 8, 3, 4, gameVectors.getWallVector(), gameTextures.getWallTexture(), gameTextures.getBoxTexture());
    gameVectors.getRoomVector().push_back(room3);
    Enemy::spawnEnemies(6, room3, gameVectors.getEnemyVector(), gameTextures.getEnemyTexture(), gameFonts.getTextFont());
    Room room4(0,0+16*Wall::getProps(), 8,8, 1, 3, gameVectors.getWallVector(), gameTextures.getWallTexture(), gameTextures.getBoxTexture());
    gameVectors.getRoomVector().push_back(room4);
    Enemy::spawnEnemies(6, room4, gameVectors.getEnemyVector(), gameTextures.getEnemyTexture(), gameFonts.getTextFont());
}

Fonts& Game::getFonts() {
    return gameFonts;
}

Textures& Game::getTextures() {
    return gameTextures;
}

Music& Game::getMusic() {
    return gameMusic;
}

Vectors& Game::getVectors() {
    return gameVectors;
}

Player& Game::getPlayer1() {
    return player1;
}

Player& Game::getPlayer2() {
    return player2;
}

sf::Text& Game::getEsCooldown() {
    return esCooldown;
}

Powerup& Game::getPowerup() {
    return powerup;
}

Pickup& Game::getCoin() {
    return coin;
}

TextDisplay& Game::getTextDisplay() {
    return textDisplay;
}

sf::Text& Game::getMoneyText() {
    return moneyText;
}

Projectile& Game::getProjectile() {
    return projectile;
}

sf::Text& Game::getHpText() {
    return hpText;
}

sf::View& Game::getView() {
    return view;
}

sf::Sprite& Game::getEchoSlamSprite() {
    return echoSlamSprite;
}

void Game::drawWalls() {
    int counter = 0;
    for(auto i = gameVectors.getWallVector().begin(); i != gameVectors.getWallVector().end(); i++) {
        if(gameVectors.getWallVector()[counter].destructable) {
            gameVectors.getWallVector()[counter].rect.setFillColor(sf::Color::Yellow);
        }
        window.draw(gameVectors.getWallVector()[counter].rect);
        window.draw(gameVectors.getWallVector()[counter].sprite);
        counter++;
    }
}

void Game::drawPlayers() {
    window.draw(player1.sprite);
    window.draw(player2.sprite);
}

void Game::drawProjectiles() {
    int prCounter = 0;
    for(auto i = gameVectors.getProjectileVector().begin(); i != gameVectors.getProjectileVector().end(); i++) {
        gameVectors.getProjectileVector()[prCounter].update();
        window.draw(gameVectors.getProjectileVector()[prCounter].sprite);
        prCounter++;
    }
}

void Game::drawEnemies() {
    int enemyCoutner = 0;
    for(auto i = gameVectors.getEnemyVector().begin(); i != gameVectors.getEnemyVector().end(); i++) {
        gameVectors.getEnemyVector()[enemyCoutner].update();
        gameVectors.getEnemyVector()[enemyCoutner].updateMovement();
        window.draw(gameVectors.getEnemyVector()[enemyCoutner].sprite);
        window.draw(gameVectors.getEnemyVector()[enemyCoutner].text);
        enemyCoutner++;
    }
}

void Game::drawCoins() {
    int counter = 0;
    for(auto i = gameVectors.getPickupVector().begin(); i != gameVectors.getPickupVector().end(); i++) {
        gameVectors.getPickupVector()[counter].update();
        window.draw(gameVectors.getPickupVector()[counter].sprite);
        counter++;
    }
}

void Game::drawPowerups() {
    int counter = 0;
    for(auto i = gameVectors.getPowerupVector().begin(); i != gameVectors.getPowerupVector().end(); i++) {
        gameVectors.getPowerupVector()[counter].update();
        window.draw(gameVectors.getPowerupVector()[counter].sprite);
        counter++;
    }
}

void Game::drawHeals() {
    int counter = 0;
    for(auto i = gameVectors.getHealVector().begin(); i != gameVectors.getHealVector().end(); i++) {
        window.draw(gameVectors.getHealVector()[counter].sprite);
        window.draw(gameVectors.getHealVector()[counter].text);
        counter++;
    }
}

void Game::drawTexts() {
    int counter = 0;
    for(auto i = gameVectors.getTextDisplayVector().begin(); i != gameVectors.getTextDisplayVector().end(); i++) {
        gameVectors.getTextDisplayVector()[counter].update();
        window.draw(gameVectors.getTextDisplayVector()[counter].text);
        counter++;
    }
}

void Game::playerWallCollision() {
    int counter = 0;
    for(auto i = gameVectors.getWallVector().begin(); i != gameVectors.getWallVector().end(); i++) {
        if(player1.rect.getGlobalBounds().intersects(gameVectors.getWallVector()[counter].rect.getGlobalBounds())) {
            if(player1.direction == 1) {
                player1.canMoveUp = false;
                player1.rect.move(0,player1.movementSpeed+2);
                player1.update();
            }
            else if(player1.direction == 2) {
                player1.canMoveDown = false;
                player1.rect.move(0,-player1.movementSpeed-2);
                player1.update();
            }
            else if(player1.direction == 3) {
                player1.canMoveLeft = false;
                player1.rect.move(player1.movementSpeed+2,0);
                player1.update();
            }
            else if(player1.direction == 4) {
                player1.canMoveRight = false;
                player1.rect.move(-player1.movementSpeed-2,0);
                player1.update();   
            }
        }
        counter++;
    }
}

void Game::enemyWallCollision() {
    int counter = 0;
    for(auto i = gameVectors.getEnemyVector().begin(); i != gameVectors.getEnemyVector().end(); i++) {
        int counter2 = 0;
        for(auto j = gameVectors.getWallVector().begin(); j != gameVectors.getWallVector().end(); j++) {
            if(gameVectors.getEnemyVector()[counter].rect.getGlobalBounds().intersects(gameVectors.getWallVector()[counter2].rect.getGlobalBounds())) {
                if(gameVectors.getEnemyVector()[counter].direction == 1) {
                    gameVectors.getEnemyVector()[counter].canMoveUp = false;
                    gameVectors.getEnemyVector()[counter].rect.move(0,gameVectors.getEnemyVector()[counter].movementSpeed);
                    gameVectors.getEnemyVector()[counter].update();
                }
                else if(gameVectors.getEnemyVector()[counter].direction == 2) {
                    gameVectors.getEnemyVector()[counter].canMoveDown = false;
                    gameVectors.getEnemyVector()[counter].rect.move(0,-gameVectors.getEnemyVector()[counter].movementSpeed);
                    gameVectors.getEnemyVector()[counter].update();
                }
                else if(gameVectors.getEnemyVector()[counter].direction == 3) {
                    gameVectors.getEnemyVector()[counter].canMoveLeft = false;
                    gameVectors.getEnemyVector()[counter].rect.move(gameVectors.getEnemyVector()[counter].movementSpeed,0);
                    gameVectors.getEnemyVector()[counter].update();
                }
                else if(gameVectors.getEnemyVector()[counter].direction == 4) {
                    gameVectors.getEnemyVector()[counter].canMoveRight = false;
                    gameVectors.getEnemyVector()[counter].rect.move(-gameVectors.getEnemyVector()[counter].movementSpeed,0);
                    gameVectors.getEnemyVector()[counter].update();
                }
            }
            counter2++;
        }
        counter++;
    }
}

void Game::playerPickupCollision() {
    int counter = 0;
    for(auto i = gameVectors.getPickupVector().begin(); i != gameVectors.getPickupVector().end(); i++) {
        if(gameVectors.getPickupVector()[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
            if(gameVectors.getPickupVector()[counter].isCoin) {
                gameMusic.getCoinSound().play();
                player1.money += 15;
            }
            gameVectors.getPickupVector()[counter].destroy = true;
        }
        counter++;
    }
}

void Game::playerHealCollision(sf::Clock& coolDown) {
    int counter = 0;
    for(auto i = gameVectors.getHealVector().begin(); i != gameVectors.getHealVector().end(); i++) {
        if(coolDown.getElapsedTime().asSeconds() >= gameVectors.getHealVector()[counter].coolDownDuration && gameVectors.getHealVector()[counter].isOnCoolDown == true) {
            gameVectors.getHealVector()[counter].isOnCoolDown = false;
            gameVectors.getHealVector()[counter].update();
        }
        if(player1.rect.getGlobalBounds().intersects(gameVectors.getHealVector()[counter].rect.getGlobalBounds())) {
            if(player1.money >= gameVectors.getHealVector()[counter].price && gameVectors.getHealVector()[counter].isOnCoolDown == false) {
                player1.money -= gameVectors.getHealVector()[counter].price;
                player1.hp += 25;
                gameVectors.getHealVector()[counter].isOnCoolDown = true;
                coolDown.restart();
                gameVectors.getHealVector()[counter].update();
            }
        }
        counter++;
    }
}

void Game::playerPowerupCollision() {
    int counter = 0;
    for(auto i = gameVectors.getPowerupVector().begin(); i != gameVectors.getPowerupVector().end(); i++) {
        if(player1.rect.getGlobalBounds().intersects(gameVectors.getPowerupVector()[counter].rect.getGlobalBounds())) {
            player1.powerupLevel++;
            gameVectors.getPowerupVector()[counter].destroy = true;
        }
        counter++;
    }
}

void Game::enemyProjectilePlayerCollision() {
    int counter = 0;
    for(auto i = gameVectors.getProjectileVector().begin(); i != gameVectors.getProjectileVector().end(); i++) {
        if(gameVectors.getProjectileVector()[counter].enemyProjectile && gameVectors.getProjectileVector()[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
            gameMusic.getCollisionSound().play();
            gameVectors.getProjectileVector()[counter].destroy = true;
            textDisplay.text.setString("-" + std::to_string(gameVectors.getProjectileVector()[counter].attackDamage));
            textDisplay.text.setPosition(player1.rect.getPosition().x + 20, player1.rect.getPosition().y - 20);
            textDisplay.text.setColor(sf::Color::Black);
            gameVectors.getTextDisplayVector().push_back(textDisplay);
            player1.hp -= gameVectors.getProjectileVector()[counter].attackDamage;
        }
    }
}

void Game::projectileEnemyCollision() {
    int counter = 0;
    for(auto i = gameVectors.getProjectileVector().begin(); i != gameVectors.getProjectileVector().end(); i++) {
        int counter2 = 0;
        for(auto j = gameVectors.getEnemyVector().begin(); j != gameVectors.getEnemyVector().end(); j++) {
            if(!gameVectors.getProjectileVector()[counter].enemyProjectile && gameVectors.getProjectileVector()[counter].rect.getGlobalBounds().intersects(gameVectors.getEnemyVector()[counter2].rect.getGlobalBounds())) {
                gameMusic.getCollisionSound().play();
                gameVectors.getEnemyVector()[counter2].isAggro = true;
                textDisplay.text.setString("-" + std::to_string(player1.attackDamage));
                textDisplay.text.setPosition(gameVectors.getEnemyVector()[counter2].rect.getPosition().x + 16, gameVectors.getEnemyVector()[counter2].rect.getPosition().y - 16);
                textDisplay.text.setColor(sf::Color::Red);
                gameVectors.getTextDisplayVector().push_back(textDisplay);
                gameVectors.getProjectileVector()[counter].destroy = true;
                gameVectors.getEnemyVector()[counter2].hp -= player1.attackDamage;
                if(gameVectors.getEnemyVector()[counter2].hp <= 0) {
                    gameVectors.getEnemyVector()[counter2].alive = false;
                }
            }
            counter2++;
        }
        counter++;
    }
}

void Game::wallProjectileCollision() {
    int counter = 0;
    for(auto i = gameVectors.getProjectileVector().begin(); i != gameVectors.getProjectileVector().end(); i++) {
        int counter2 = 0;
        for(auto j = gameVectors.getWallVector().begin(); j != gameVectors.getWallVector().end(); j++) {
            if(gameVectors.getProjectileVector()[counter].rect.getGlobalBounds().intersects(gameVectors.getWallVector()[counter2].rect.getGlobalBounds())) {
                gameVectors.getProjectileVector()[counter].destroy = true;
                if(gameVectors.getWallVector()[counter2].destructable == true) {
                    gameVectors.getWallVector()[counter2].hp -= player1.attackDamage;
                }
            }
            counter2++;
        }
        counter++;
    }
}

void Game::enemyPlayerCollision(sf::Clock clock2, sf::Time elapsed2) {
    if(elapsed2.asSeconds() >= 0.42) {
        int counter = 0;
        clock2.restart();
        for(auto i = gameVectors.getEnemyVector().begin(); i != gameVectors.getEnemyVector().end(); i++) {
            if(gameVectors.getEnemyVector()[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
                textDisplay.text.setString(std::to_string(player1.hp));
                textDisplay.text.setPosition(player1.rect.getPosition().x + 16, player1.rect.getPosition().y - 16);
                gameVectors.getTextDisplayVector().push_back(textDisplay);
                player1.hp -= gameVectors.getEnemyVector()[counter].attackDamage;
                player1.powerupLevel = 0;
            }
            counter++;
        }
    }
}

void Game::resetLimits() {
    bool canReset = true;
    int counter = 0;
    for(auto i = gameVectors.getWallVector().begin(); i != gameVectors.getWallVector().end(); i++) {
        if(gameVectors.getWallVector()[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
            canReset = false;
        }
    }
    if(canReset)
        player1.resetMoveLimits();
}

void Game::destroyPowerup() {
    int counter = 0;
    for(auto i = gameVectors.getPowerupVector().begin(); i != gameVectors.getPowerupVector().end(); i++) {
        if(gameVectors.getPowerupVector()[counter].destroy == true) {
            gameVectors.getPowerupVector().erase(i);
            break;
        }
        counter++;
    }
}

void Game::destroyWall() {
    int counter = 0;
    for(auto i = gameVectors.getWallVector().begin(); i != gameVectors.getWallVector().end(); i++) {
        if(gameVectors.getWallVector()[counter].hp < 0) {
            gameVectors.getWallVector().erase(i);
            break;
        }
        counter++;
    }
}

void Game::destroyCoin() {
    int counter = 0;
    for(auto i = gameVectors.getPickupVector().begin(); i != gameVectors.getPickupVector().end(); i++) {
        if(gameVectors.getPickupVector()[counter].destroy == true) {
            gameVectors.getPickupVector().erase(i);
            break;
        }
        counter++;
    }
}

void Game::destroyText() {
    int counter = 0;
    for(auto i = gameVectors.getTextDisplayVector().begin(); i != gameVectors.getTextDisplayVector().end(); i++) {
        if(gameVectors.getTextDisplayVector()[counter].destroy == true) {
            gameVectors.getTextDisplayVector().erase(i);
            break;
        }
        counter++;
    }
}

void Game::destroyEnemy() {
    int counter = 0;
    for(auto i = gameVectors.getEnemyVector().begin(); i != gameVectors.getEnemyVector().end(); i++) {
        if(gameVectors.getEnemyVector()[counter].alive == false) {
            if(generateRandom(5) == 4) {
                coin.rect.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition().x, gameVectors.getEnemyVector()[counter].rect.getPosition().y);
                gameVectors.getPickupVector().push_back(coin);
            }
            if(generateRandom(10) == 5) {
                powerup.rect.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition());
                gameVectors.getPowerupVector().push_back(powerup);
            }
            gameVectors.getEnemyVector().erase(i);
            break;
        }
        counter++;
    }
}

void Game::destroyProjectile() {
    int counter = 0;
    for(auto i = gameVectors.getProjectileVector().begin(); i != gameVectors.getProjectileVector().end(); i++) {
        if(gameVectors.getProjectileVector()[counter].destroy == true) {
            gameVectors.getProjectileVector().erase(i);
            break;
        }
    }
}

void Game::fire(sf::Clock& clock1, sf::Time& elapsed1, bool isFocused) {
    if(elapsed1.asSeconds() >= 0.1 && isFocused) {
        clock1.restart();
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            projectile.direction = player1.direction;
            projectile.rect.setPosition(player1.rect.getPosition().x+player1.rect.getSize().x/2 - projectile.rect.getSize().x/2, player1.rect.getPosition().y+player1.rect.getSize().y/2-projectile.rect.getSize().y/2);
            projectile.sprite.setTextureRect(sf::IntRect(0,0,32,32));
            gameVectors.getProjectileVector().push_back(projectile);
            gameMusic.getShotSound().play();

            if(player1.powerupLevel == 1) {
                projectile.rect.setPosition(player1.rect.getPosition().x+player1.rect.getSize().x/2+16 - projectile.rect.getSize().x/2, player1.rect.getPosition().y+player1.rect.getSize().y/2+16 - projectile.rect.getSize().y/2);
                gameVectors.getProjectileVector().push_back(projectile);
            }

            if(player1.powerupLevel >= 2) {
                for(int i = 1; i <= 4; i++) {
                    if(i == player1.direction) {
                        continue;
                    }
                    projectile.direction = i;
                    gameVectors.getProjectileVector().push_back(projectile);
                }
            }
        }
    }
}

void Game::aggro(sf::Clock& clock3, sf::Time& elapsed3) {
    int counter = 0;
    for(auto i = gameVectors.getEnemyVector().begin(); i != gameVectors.getEnemyVector().end(); i++) {
        if(gameVectors.getEnemyVector()[counter].isAggro) {
            if(std::abs(gameVectors.getEnemyVector()[counter].rect.getPosition().x - player1.rect.getPosition().x) >= 250 || std::abs(gameVectors.getEnemyVector()[counter].rect.getPosition().y - player1.rect.getPosition().y) >= 250) {
                gameVectors.getEnemyVector()[counter].isAggro = false;
                std::cout << "Enemy aggro: false" << std::endl;
                continue;
            }

            if(elapsed3.asSeconds() >= 1) {
                clock3.restart();
                int enemyAction = generateRandom(3);

                projectile.attackDamage = gameVectors.getEnemyVector()[counter].attackDamage;

                if(enemyAction == 1) {
                    if(player1.rect.getPosition().x < gameVectors.getEnemyVector()[counter].rect.getPosition().x && std::abs(player1.rect.getPosition().y - gameVectors.getEnemyVector()[counter].rect.getPosition().y) <= 40) {
                        gameMusic.getShotSound().play();
                        projectile.enemyProjectile = true;
                        projectile.direction = 3;
                        projectile.rect.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition());
                        gameVectors.getProjectileVector().push_back(projectile);
                        projectile.enemyProjectile = false;

                        gameVectors.getEnemyVector()[counter].direction = 3;
                    }

                    if(player1.rect.getPosition().x > gameVectors.getEnemyVector()[counter].rect.getPosition().x && std::abs(player1.rect.getPosition().y - gameVectors.getEnemyVector()[counter].rect.getPosition().y) <= 40) {
                        gameMusic.getShotSound().play();
                        projectile.enemyProjectile = true;
                        projectile.direction = 4;
                        projectile.rect.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition());
                        gameVectors.getProjectileVector().push_back(projectile);
                        projectile.enemyProjectile = false;

                        gameVectors.getEnemyVector()[counter].direction = 4;
                    }

                    if(player1.rect.getPosition().y < gameVectors.getEnemyVector()[counter].rect.getPosition().y && std::abs(player1.rect.getPosition().x - gameVectors.getEnemyVector()[counter].rect.getPosition().x) <= 40) {
                        gameMusic.getShotSound().play();
                        projectile.enemyProjectile = true;
                        projectile.direction = 1;
                        projectile.rect.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition());
                        gameVectors.getProjectileVector().push_back(projectile);
                        projectile.enemyProjectile = false;

                        gameVectors.getEnemyVector()[counter].direction = 1;
                    }

                    if(player1.rect.getPosition().y > gameVectors.getEnemyVector()[counter].rect.getPosition().y && std::abs(player1.rect.getPosition().x - gameVectors.getEnemyVector()[counter].rect.getPosition().x) <= 40) {
                        gameMusic.getShotSound().play();
                        projectile.enemyProjectile = true;
                        projectile.direction = 2;
                        projectile.rect.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition());
                        gameVectors.getProjectileVector().push_back(projectile);
                        projectile.enemyProjectile = false;

                        gameVectors.getEnemyVector()[counter].direction = 2;
                    }
                }
            }
        }
        counter++;
    }
}

void Game::echoSlamCast(sf::Clock& echoSlamCoolDown, bool isFocused) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && player1.echoSlam.readyToCast && isFocused) {
        int counter = 0;
        for(auto i = gameVectors.getEnemyVector().begin(); i != gameVectors.getEnemyVector().end(); i++) {
            if(player1.rect.getPosition().x - gameVectors.getEnemyVector()[counter].rect.getPosition().x <= 300 && player1.rect.getPosition().x - gameVectors.getEnemyVector()[counter].rect.getPosition().x >= -300) {
                if(player1.rect.getPosition().y - gameVectors.getEnemyVector()[counter].rect.getPosition().y <= 300 && player1.rect.getPosition().y - gameVectors.getEnemyVector()[counter].rect.getPosition().y >= -300) {
                    gameMusic.getEchoSlamSound().play();
                    textDisplay.text.setString("-" + std::to_string(player1.echoSlam.getDamage()));
                    textDisplay.text.setPosition(gameVectors.getEnemyVector()[counter].rect.getPosition().x + 16, gameVectors.getEnemyVector()[counter].rect.getPosition().y - 16);
                    textDisplay.text.setColor(sf::Color::Red);
                    gameVectors.getTextDisplayVector().push_back(textDisplay);
                    gameVectors.getEnemyVector()[counter].hp -= player1.echoSlam.getDamage();
                    if(gameVectors.getEnemyVector()[counter].hp <= 0) {
                        gameVectors.getEnemyVector()[counter].alive = false;
                    }
                }
            }
            counter++;
        }
        player1.echoSlam.readyToCast = false;
        echoSlamCoolDown.restart();
    }
}

void Game::checkEchoCastReady(sf::Clock& echoSlamCoolDown, bool isFocused) {
    if(!player1.echoSlam.readyToCast && isFocused) {
        if(echoSlamCoolDown.getElapsedTime().asSeconds() >= player1.echoSlam.getSpellCoolDown()) {
            player1.echoSlam.readyToCast = true;
        }
    }
}

void Game::textManipulations() {
    moneyText.setPosition(view.getCenter().x-300, view.getCenter().y-200);
    moneyText.setString("Money: "+std::to_string(player1.money));
    hpText.setPosition(view.getCenter().x-300, view.getCenter().y-180);
    hpText.setString("HP: "+std::to_string(player1.hp));        
    echoSlamSprite.setPosition(view.getCenter().x-300, view.getCenter().y-100);
}