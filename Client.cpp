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

    sf::Packet packet;
    sf::TcpSocket socket;

    std::string ipBuff;

    std::cout << "Input IP address of server: ";
    std::cin >> ipBuff;
    std::cout << "INPUT IP IS > " << ipBuff << std::endl;

    sf::IpAddress serverIP(ipBuff);
    socket.connect(serverIP, 2241);

    bool done = false;
    bool isFirstConnect = true;

    socket.setBlocking(true);

    int packetType;

    while(!done) {
        socket.receive(packet);
        sf::Vector2f buffPos;
        int uniqueGeneratedID;
        if(packet >> packetType >> buffPos.x >> buffPos.y >> uniqueGeneratedID && packetType == 0) {
            mainPlayer.uniqueID = uniqueGeneratedID;
            mainPlayer.rect.setPosition(buffPos);
            mainPlayer.sprite.setTexture(textureCharacter);
            playersOnServer.push_back(mainPlayer);
            done = true;
        }
        clientID = uniqueGeneratedID;
        isFirstConnect = false;
    }

    //*************************** FONTS **************************************

    sf::Font textFont;
    textFont.loadFromFile("sansation.ttf");

    //**************************** GENERATING MAIN GAMEPLAY OBJECTS **********************************

    //Generating the main window
    sf::RenderWindow window(sf::VideoMode(1024, 680), "SFML window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    //******************************************** UI TEXT *********************************************

    sf::Vector2f prevPlayerPosition;


    while(window.isOpen()) {
        packet.clear();
        
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
            packet << playersOnServer[0].rect.getPosition().x << playersOnServer[0].rect.getPosition().y << clientID;
            socket.send(packet);
            packet.clear();
        }

        if(packet) {
            
        }

        window.display();
    }
}