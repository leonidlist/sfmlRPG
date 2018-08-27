#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Projectile.h"
#include "Enemy.h"
#include "TextDisplay.h"
#include "Pickup.h"
#include "Wall.h"
#include "Powerup.h"
#include "Room.h"
#include "Heal.h"
#include "Game.hpp"
#include <vector>

int main(int, char const**)
{
    srand(5);

    //Variables
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clock3;

    bool inMenu = true;

    bool isFocused = true;

    sf::Clock coolDown;
    sf::Clock echoSlamCoolDown;

    //********************* NETWORK *********************************

    sf::Vector2f prevPosition;
    sf::Vector2f buffPos;
    sf::Packet packet;
    sf::IpAddress ip;
    sf::TcpSocket socket;
    char connectionType;
    std::cout << "Enter (s) for server, enter (c) for client >> ";
    std::cin >> connectionType;
    if(connectionType == 's') {
        sf::TcpListener listener;
        listener.listen(2241);
        listener.accept(socket);
    }
    else {
        std::cout << "Input ip address >> ";
        std::string ipBuff;
        std::cin >> ipBuff;
        ip = sf::IpAddress(ipBuff);
        socket.connect(ip, 2241);
    }
    socket.setBlocking(false);

    // MAIN GAME OBJECT

    Game MAINGAME(sf::VideoMode(1024, 840), "MAIN");
    MAINGAME.generateLocation();

    //**************************** GENERATING MAIN GAMEPLAY OBJECTS **********************************

    Heal heal1(MAINGAME.getTextures().getHealTexture(), MAINGAME.getVectors().getRoomVector()[3].startX + ((MAINGAME.getVectors().getRoomVector()[3].endX - MAINGAME.getVectors().getRoomVector()[3].startX)/2), MAINGAME.getVectors().getRoomVector()[3].startY + ((MAINGAME.getVectors().getRoomVector()[3].endY - MAINGAME.getVectors().getRoomVector()[3].startY)/2), MAINGAME.getFonts().getTextFont());
    MAINGAME.getVectors().getHealVector().push_back(heal1);

    //******************************************* MAIN LOOP ****************************************************************************8

    while (MAINGAME.getWindow().isOpen())
    {
        sf::Time elapsed1 = clock1.getElapsedTime();
        sf::Time elapsed2 = clock2.getElapsedTime();
        sf::Time elapsed3 = clock3.getElapsedTime();

        prevPosition = MAINGAME.getPlayer1().rect.getPosition();

        MAINGAME.getWindow().setView(MAINGAME.getView());

        //****************************** HANDLING EVENTS ******************************

        sf::Event event;//Enemy generation
        while (MAINGAME.getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                MAINGAME.getWindow().close();
            }
            //Zoom in/out
            if(event.type == sf::Event::MouseWheelMoved) {
                if(event.mouseWheel.delta > 0)
                    MAINGAME.getView().zoom(0.95);
                else if(event.mouseWheel.delta < 0)
                    MAINGAME.getView().zoom(1.05);
            }
            if(event.type == sf::Event::LostFocus) {
                isFocused = false;
            }
            if(event.type == sf::Event::GainedFocus) {
                isFocused = true;
            }
        }

        // Clear screen
        MAINGAME.getWindow().clear(sf::Color::White);

        //**************************** RENDERING OBJECTS *********************************

        MAINGAME.drawWalls();
        MAINGAME.drawPlayers();
        MAINGAME.drawProjectiles();
        MAINGAME.drawEnemies();
        MAINGAME.drawCoins();
        MAINGAME.drawPowerups();
        MAINGAME.drawHeals();
        MAINGAME.drawTexts();

        //*************************************** COLLISIONS *******************************************

        MAINGAME.playerWallCollision();
        MAINGAME.enemyWallCollision();
        MAINGAME.playerPickupCollision();
        MAINGAME.playerHealCollision(coolDown);
        MAINGAME.playerPickupCollision();
        MAINGAME.enemyProjectilePlayerCollision();
        MAINGAME.projectileEnemyCollision();
        MAINGAME.wallProjectileCollision();
        MAINGAME.enemyPlayerCollision(clock2, elapsed2);
        MAINGAME.resetLimits();
        
        //Enemy Aggro
        counter = 0;
        for(auto i = MAINGAME.getVectors().getEnemyVector().begin(); i != MAINGAME.getVectors().getEnemyVector().end(); i++) {
            if(MAINGAME.getVectors().getEnemyVector()[counter].isAggro) {
                if(std::abs(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x - MAINGAME.getPlayer1().rect.getPosition().x) >= 250 || std::abs(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y - MAINGAME.getPlayer1().rect.getPosition().y) >= 250) {
                    MAINGAME.getVectors().getEnemyVector()[counter].isAggro = false;
                    std::cout << "Enemy aggro: false" << std::endl;
                    continue;
                }

                if(elapsed3.asSeconds() >= 1) {
                    clock3.restart();
                    int enemyAction = generateRandom(3);

                    MAINGAME.getProjectile().attackDamage = MAINGAME.getVectors().getEnemyVector()[counter].attackDamage;

                    if(enemyAction == 1) {
                        if(MAINGAME.getPlayer1().rect.getPosition().x < MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x && std::abs(MAINGAME.getPlayer1().rect.getPosition().y - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y) <= 40) {
                            MAINGAME.getMusic().getShotSound().play();
                            MAINGAME.getProjectile().enemyProjectile = true;
                            MAINGAME.getProjectile().direction = 3;
                            MAINGAME.getProjectile().rect.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition());
                            MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                            MAINGAME.getProjectile().enemyProjectile = false;

                            MAINGAME.getVectors().getEnemyVector()[counter].direction = 3;
                        }

                        if(MAINGAME.getPlayer1().rect.getPosition().x > MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x && std::abs(MAINGAME.getPlayer1().rect.getPosition().y - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y) <= 40) {
                            MAINGAME.getMusic().getShotSound().play();
                            MAINGAME.getProjectile().enemyProjectile = true;
                            MAINGAME.getProjectile().direction = 4;
                            MAINGAME.getProjectile().rect.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition());
                            MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                            MAINGAME.getProjectile().enemyProjectile = false;

                            MAINGAME.getVectors().getEnemyVector()[counter].direction = 4;
                        }

                        if(MAINGAME.getPlayer1().rect.getPosition().y < MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y && std::abs(MAINGAME.getPlayer1().rect.getPosition().x - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x) <= 40) {
                            MAINGAME.getMusic().getShotSound().play();
                            MAINGAME.getProjectile().enemyProjectile = true;
                            MAINGAME.getProjectile().direction = 1;
                            MAINGAME.getProjectile().rect.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition());
                            MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                            MAINGAME.getProjectile().enemyProjectile = false;

                            MAINGAME.getVectors().getEnemyVector()[counter].direction = 1;
                        }

                        if(MAINGAME.getPlayer1().rect.getPosition().y > MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y && std::abs(MAINGAME.getPlayer1().rect.getPosition().x - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x) <= 40) {
                            MAINGAME.getMusic().getShotSound().play();
                            MAINGAME.getProjectile().enemyProjectile = true;
                            MAINGAME.getProjectile().direction = 2;
                            MAINGAME.getProjectile().rect.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition());
                            MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                            MAINGAME.getProjectile().enemyProjectile = false;

                            MAINGAME.getVectors().getEnemyVector()[counter].direction = 2;
                        }
                    }
                }
            }
            counter++;
        }

        //************************************* DESTROY ITEMS ***************************************

        //Destroy picked up powerup
        counter = 0;
        for(auto i = MAINGAME.getVectors().getPowerupVector().begin(); i != MAINGAME.getVectors().getPowerupVector().end(); i++) {
            if(MAINGAME.getVectors().getPowerupVector()[counter].destroy == true) {
                MAINGAME.getVectors().getPowerupVector().erase(i);
                break;
            }
            counter++;
        }

        //Destroy wall
        counter = 0;
        for(auto i = MAINGAME.getVectors().getWallVector().begin(); i != MAINGAME.getVectors().getWallVector().end(); i++) {
            if(MAINGAME.getVectors().getWallVector()[counter].hp < 0) {
                MAINGAME.getVectors().getWallVector().erase(i);
                break;
            }
            counter++;
        }

        //Destroy coins
        counter = 0;
        for(auto i = MAINGAME.getVectors().getPickupVector().begin(); i != MAINGAME.getVectors().getPickupVector().end(); i++) {
            if(MAINGAME.getVectors().getPickupVector()[counter].destroy == true) {
                MAINGAME.getVectors().getPickupVector().erase(i);
                break;
            }
            counter++;
        }

        //Destroy text
        counter = 0;
        for(auto i = MAINGAME.getVectors().getTextDisplayVector().begin(); i != MAINGAME.getVectors().getTextDisplayVector().end(); i++) {
            if(MAINGAME.getVectors().getTextDisplayVector()[counter].destroy == true) {
                MAINGAME.getVectors().getTextDisplayVector().erase(i);
                break;
            }
            counter++;
        }

        //Destroy dead enemy
        counter = 0;
        for(auto i = MAINGAME.getVectors().getEnemyVector().begin(); i != MAINGAME.getVectors().getEnemyVector().end(); i++) {
            if(MAINGAME.getVectors().getEnemyVector()[counter].alive == false) {
                if(generateRandom(5) == 4) {
                    MAINGAME.getCoin().rect.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x, MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y);
                    MAINGAME.getVectors().getPickupVector().push_back(MAINGAME.getCoin());
                }
                if(generateRandom(10) == 5) {
                    MAINGAME.getPowerup().rect.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition());
                    MAINGAME.getVectors().getPowerupVector().push_back(MAINGAME.getPowerup());
                }
                MAINGAME.getVectors().getEnemyVector().erase(i);
                break;
            }
            counter++;
        }

        //Destory projectiles
        counter = 0;
        for(auto i = MAINGAME.getVectors().getProjectileVector().begin(); i != MAINGAME.getVectors().getProjectileVector().end(); i++) {
            if(MAINGAME.getVectors().getProjectileVector()[counter].destroy == true) {
                MAINGAME.getVectors().getProjectileVector().erase(i);
                break;
            }
        }

        //************************************** OTHER **********************************************

        //Fire Missle
        if(elapsed1.asSeconds() >= 0.1 && isFocused) {
            clock1.restart();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                MAINGAME.getProjectile().direction = MAINGAME.getPlayer1().direction;
                MAINGAME.getProjectile().rect.setPosition(MAINGAME.getPlayer1().rect.getPosition().x+MAINGAME.getPlayer1().rect.getSize().x/2 - MAINGAME.getProjectile().rect.getSize().x/2, MAINGAME.getPlayer1().rect.getPosition().y+MAINGAME.getPlayer1().rect.getSize().y/2-MAINGAME.getProjectile().rect.getSize().y/2);
                MAINGAME.getProjectile().sprite.setTextureRect(sf::IntRect(0,0,32,32));
                MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                MAINGAME.getMusic().getShotSound().play();

                if(MAINGAME.getPlayer1().powerupLevel == 1) {
                    MAINGAME.getProjectile().rect.setPosition(MAINGAME.getPlayer1().rect.getPosition().x+MAINGAME.getPlayer1().rect.getSize().x/2+16 - MAINGAME.getProjectile().rect.getSize().x/2, MAINGAME.getPlayer1().rect.getPosition().y+MAINGAME.getPlayer1().rect.getSize().y/2+16 - MAINGAME.getProjectile().rect.getSize().y/2);
                    MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                }

                if(MAINGAME.getPlayer1().powerupLevel >= 2) {
                    for(int i = 1; i <= 4; i++) {
                        if(i == MAINGAME.getPlayer1().direction) {
                            continue;
                        }
                        MAINGAME.getProjectile().direction = i;
                        MAINGAME.getVectors().getProjectileVector().push_back(MAINGAME.getProjectile());
                    }
                }
            }
        }

        if(!MAINGAME.getPlayer1().echoSlam.readyToCast && isFocused) {
            if(echoSlamCoolDown.getElapsedTime().asSeconds() >= MAINGAME.getPlayer1().echoSlam.getSpellCoolDown()) {
                MAINGAME.getPlayer1().echoSlam.readyToCast = true;
            }
        }

        //Echo slam
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && MAINGAME.getPlayer1().echoSlam.readyToCast && isFocused) {
            counter = 0;
            for(auto i = MAINGAME.getVectors().getEnemyVector().begin(); i != MAINGAME.getVectors().getEnemyVector().end(); i++) {
                if(MAINGAME.getPlayer1().rect.getPosition().x - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x <= 300 && MAINGAME.getPlayer1().rect.getPosition().x - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x >= -300) {
                    if(MAINGAME.getPlayer1().rect.getPosition().y - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y <= 300 && MAINGAME.getPlayer1().rect.getPosition().y - MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y >= -300) {
                        MAINGAME.getMusic().getEchoSlamSound().play();
                        MAINGAME.getTextDisplay().text.setString("-" + std::to_string(MAINGAME.getPlayer1().echoSlam.getDamage()));
                        MAINGAME.getTextDisplay().text.setPosition(MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().x + 16, MAINGAME.getVectors().getEnemyVector()[counter].rect.getPosition().y - 16);
                        MAINGAME.getTextDisplay().text.setColor(sf::Color::Red);
                        MAINGAME.getVectors().getTextDisplayVector().push_back(MAINGAME.getTextDisplay());
                        MAINGAME.getVectors().getEnemyVector()[counter].hp -= MAINGAME.getPlayer1().echoSlam.getDamage();
                        if(MAINGAME.getVectors().getEnemyVector()[counter].hp <= 0) {
                            MAINGAME.getVectors().getEnemyVector()[counter].alive = false;
                        }
                    }
                }
                counter++;
            }
            MAINGAME.getPlayer1().echoSlam.readyToCast = false;
            echoSlamCoolDown.restart();
        }

        MAINGAME.getMoneyText().setPosition(MAINGAME.getView().getCenter().x-300, MAINGAME.getView().getCenter().y-200);
        MAINGAME.getMoneyText().setString("Money: "+std::to_string(MAINGAME.getPlayer1().money));
        MAINGAME.getHpText().setPosition(MAINGAME.getView().getCenter().x-300, MAINGAME.getView().getCenter().y-180);
        MAINGAME.getHpText().setString("HP: "+std::to_string(MAINGAME.getPlayer1().hp));        
        MAINGAME.getEchoSlamSprite().setPosition(MAINGAME.getView().getCenter().x-300, MAINGAME.getView().getCenter().y-100);
        MAINGAME.getWindow().draw(MAINGAME.getMoneyText());
        MAINGAME.getWindow().draw(MAINGAME.getHpText());
        if(MAINGAME.getPlayer1().echoSlam.readyToCast)
            MAINGAME.getWindow().draw(MAINGAME.getEchoSlamSprite());
        else {
            MAINGAME.getEsCooldown().setString(std::to_string(MAINGAME.getPlayer1().echoSlam.getSpellCoolDown() - (int)echoSlamCoolDown.getElapsedTime().asSeconds()));
            MAINGAME.getEsCooldown().setPosition(MAINGAME.getView().getCenter().x-300, MAINGAME.getView().getCenter().y-100);
            MAINGAME.getWindow().draw(MAINGAME.getEsCooldown());
        }

        if(isFocused) {
            MAINGAME.getPlayer1().update();
            MAINGAME.getPlayer1().updateMovement();
        }

        if(prevPosition != MAINGAME.getPlayer1().rect.getPosition()) {
            packet << MAINGAME.getPlayer1().rect.getPosition().x << MAINGAME.getPlayer1().rect.getPosition().y;
            socket.send(packet);
        }

        socket.receive(packet);
        if(packet >> buffPos.x >> buffPos.y) {
            MAINGAME.getPlayer2().rect.setPosition(buffPos);
            MAINGAME.getPlayer2().update();
            MAINGAME.getPlayer2().updateMovement();
        }

        MAINGAME.getView().setCenter(MAINGAME.getPlayer1().rect.getPosition());
        MAINGAME.getWindow().display();
    }
    return EXIT_SUCCESS;
}