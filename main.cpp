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
    bool isDie = false;
    sf::Clock coolDown;
    sf::Clock echoSlamCoolDown;

    sf::Vector2f prevPosition;
    sf::Vector2f buffPos;
    sf::Packet packet;
    sf::IpAddress ip;
    sf::TcpSocket socket;
    sf::TcpListener listener;
    char connectionType;
    std::cout << "Enter (s) for server, enter (c) for client >> ";
    std::cin >> connectionType;
    unsigned short port = 35000;
    if(connectionType == 's') {
        listener.listen(port);
        listener.accept(socket);
    }
    else {
        std::cout << "Input ip address >> ";
        std::string ipBuff;
        std::cin >> ipBuff;
        ip = sf::IpAddress(ipBuff);
        socket.connect(ip, port);
    }
    socket.setBlocking(false);

    Game MAINGAME(sf::VideoMode(1024, 840), "MAIN");
    MAINGAME.generateLocation();
    sf::Image icon;
    if(!icon.loadFromFile("icon.png"))
        return EXIT_FAILURE;
    MAINGAME.getWindow().setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //**************************** GENERATING MAIN GAMEPLAY OBJECTS **********************************

    Heal heal1(MAINGAME.getTextures().getHealTexture(), MAINGAME.getVectors().getRoomVector()[3].startX + ((MAINGAME.getVectors().getRoomVector()[3].endX - MAINGAME.getVectors().getRoomVector()[3].startX)/2), MAINGAME.getVectors().getRoomVector()[3].startY + ((MAINGAME.getVectors().getRoomVector()[3].endY - MAINGAME.getVectors().getRoomVector()[3].startY)/2), MAINGAME.getFonts().getTextFont());
    MAINGAME.getVectors().getHealVector().push_back(heal1);

    //******************************************* MAIN LOOP ****************************************************************************8

    int c = 0;
    int d = 0;
    while (MAINGAME.getWindow().isOpen())
    {
        if(isDie) {
            if(d == 0) {
                std::cout << "isDie = true" << std::endl;
                MAINGAME.getMusic().getMainTheme().stop();
                MAINGAME.getMusic().getDie().play();
                d++;
            }
            c = 0;
        }
        else if(!isDie && c == 0) {
            MAINGAME.getMusic().getDie().stop();
            MAINGAME.getMusic().getMainTheme().play();
            c++;
            d = 0;
        }
           
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

        MAINGAME.getWindow().clear(sf::Color::Black);

        MAINGAME.drawPlayers();
        MAINGAME.drawWalls();
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

        isDie = MAINGAME.checkDeath();
        
        if(!isDie) {
            MAINGAME.aggro(clock3, elapsed3);
        }

        MAINGAME.destroyPowerup();
        MAINGAME.destroyWall();
        MAINGAME.destroyCoin();
        MAINGAME.destroyText();
        MAINGAME.destroyEnemy();
        MAINGAME.destroyProjectile();
        //************************************** OTHER **********************************************

        MAINGAME.fire(clock1, elapsed1, isFocused, socket);
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
            packet << 0 << MAINGAME.getPlayer1().rect.getPosition().x << MAINGAME.getPlayer1().rect.getPosition().y;
            socket.send(packet);
        }

        packet.clear();
        int t;
        if(socket.receive(packet) == sf::Socket::Done) {
            packet >> t;
        }
        int dir;
        if(t == 0) {
            std::cout << "READ 0: " << buffPos.x << " " << buffPos.x << std::endl;
            packet >> buffPos.x >> buffPos.y;
            MAINGAME.getPlayer2().rect.setPosition(buffPos);
            MAINGAME.getPlayer2().update();
            MAINGAME.getPlayer2().updateMovement();
        }
        if(t == 1) {
            packet >> dir >> buffPos.x >> buffPos.y;
            std::cout << "READ 1: " << dir << " " << buffPos.x << " " <<  buffPos.x << std::endl;
            Projectile buff;
            buff.direction = dir;
            buff.rect.setPosition(buffPos);
            buff.sprite.setTexture(MAINGAME.getTextures().getFireballTexture());
            buff.sprite.setTextureRect(sf::IntRect(0,0,32,32));
            MAINGAME.getVectors().getProjectileVector().push_back(buff);
        }

        MAINGAME.checkEnemyAmount();

        MAINGAME.getView().setCenter(MAINGAME.getPlayer1().rect.getPosition());
        MAINGAME.getWindow().display();
        packet.clear();
        t = -1;
    }
    return EXIT_SUCCESS;
}