#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#include "Game.hpp"

int main(int, char const**)
{
    srand(5);
    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clock3;
    bool isFocused = true;
    sf::Clock coolDown;
    sf::Clock echoSlamCoolDown;

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

        sf::Event event;
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

        MAINGAME.getWindow().clear(sf::Color::White);

        MAINGAME.drawWalls();
        MAINGAME.drawPlayers();
        MAINGAME.drawProjectiles();
        MAINGAME.drawEnemies();
        MAINGAME.drawCoins();
        MAINGAME.drawPowerups();
        MAINGAME.drawHeals();
        MAINGAME.drawTexts();

        MAINGAME.playerWallCollision();
        MAINGAME.enemyWallCollision();
        MAINGAME.playerPickupCollision();
        MAINGAME.playerHealCollision(coolDown);
        MAINGAME.playerPowerupCollision();
        MAINGAME.enemyProjectilePlayerCollision();
        MAINGAME.projectileEnemyCollision();
        MAINGAME.wallProjectileCollision();
        MAINGAME.enemyPlayerCollision(clock2, elapsed2);
        MAINGAME.resetLimits();
        
        MAINGAME.aggro(clock3, elapsed3);

        MAINGAME.destroyPowerup();
        MAINGAME.destroyWall();
        MAINGAME.destroyCoin();
        MAINGAME.destroyText();
        MAINGAME.destroyEnemy();
        MAINGAME.destroyProjectile();
        //************************************** OTHER **********************************************

        MAINGAME.fire(clock1, elapsed1, isFocused);
        MAINGAME.checkEchoCastReady(echoSlamCoolDown, isFocused);
        MAINGAME.echoSlamCast(echoSlamCoolDown, isFocused);
        MAINGAME.textManipulations();
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