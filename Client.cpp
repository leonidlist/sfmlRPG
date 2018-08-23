#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Player.hpp"

enum packetTypes {
    newFirstPlayer, newPlayer, updatePlayer
};

int main(int, char const**) {

    int counter = 0;
    sf::Clock clock1;
    int clientID;
    bool isFocused = true;
    Player mainPlayer;

    //**************************** TEXTURES **************************************

    //CharacterTexture
    sf::Texture textureCharacter;
    if(!textureCharacter.loadFromFile("char.png"))
        return EXIT_FAILURE;


    //**************************** VECTOR ARRAYS **************

    std::vector<Player>playersOnServer;

    //**************** NETWORK ********************

    sf::TcpSocket socket;

    std::string ipBuff;
    unsigned short serverPort;
    std::cout << "Input IP address of server: ";
    std::cin >> ipBuff;
    std::cout << "Input port of server: ";
    std::cin >> serverPort;
    sf::IpAddress serverIP(ipBuff);

    if(socket.connect(serverIP, serverPort) != sf::Socket::Done) {
        std::cout << "Can't connect to server." << std::endl;
        return 1;
    }
    std::cout << "Connected to server." << std::endl;

    bool done = false;
    bool isFirstConnect = true;

    int packetType;

    //*************************** FONTS **************************************

    sf::Font textFont;
    textFont.loadFromFile("sansation.ttf");

    //**************************** GENERATING MAIN GAMEPLAY OBJECTS **********************************

    //Generating the main window
    sf::RenderWindow window(sf::VideoMode(1024, 680), "SFML window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0,0));

    //******************************************** UI TEXT *********************************************

    sf::Vector2f prevPlayerPosition;
    sf::Vector2f buffPos;
    int uniqueGeneratedID;

    sf::Packet initPacket;
    while(!done) {
        if(socket.receive(initPacket) != sf::Socket::Done) {
            std::cout << "W8ing for receive init packet..." << std::endl;
            done = false;
        }
        if(initPacket && initPacket >> packetType >> buffPos.x >> buffPos.y >> uniqueGeneratedID) {
            std::cout << "Init packet received" << std::endl;
            std::cout << "Init packet data: " << std::endl;
            std::cout << "\tPacket type: " << packetType << std::endl;
            std::cout << "\tInit X position: " << buffPos.x << std::endl;
            std::cout << "\tInit Y position: " << buffPos.y << std::endl;
            std::cout << "\tInit UID: " << uniqueGeneratedID << std::endl;
            mainPlayer.uniqueID = uniqueGeneratedID;
            mainPlayer.rect.setPosition(buffPos);
            mainPlayer.sprite.setTexture(textureCharacter);
            playersOnServer.push_back(mainPlayer);
            clientID = uniqueGeneratedID;
            isFirstConnect = false;
            done = true;
        }
    }

    while(window.isOpen() && done) {
        prevPlayerPosition = playersOnServer[0].rect.getPosition();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::LostFocus) {
                isFocused = false;
            }
            if(event.type == sf::Event::GainedFocus) {
                isFocused = true;
            }
        }

        window.clear(sf::Color::Black);

        for(int i = 0; i < playersOnServer.size(); i++) {
            window.draw(playersOnServer[i].sprite);
        }

        if(isFocused) {
            playersOnServer[0].update();
            playersOnServer[0].updateMovement();
        }

        if(prevPlayerPosition != playersOnServer[0].rect.getPosition()) {
            sf::Packet packet;
            packet << updatePlayer << playersOnServer[0].rect.getPosition().x << playersOnServer[0].rect.getPosition().y << clientID;
            if(socket.send(packet) == sf::Socket::Done) {
                int pt, uid;
                sf::Vector2f pp;
                packet >> pt >> pp.x >> pp.y >> uid;
                std::cout << "Sent packet with data: " << pt << " " << pp.x << ":" << pp.y << " " << uid << std::endl;
            }
        }

        window.display();
    }
}