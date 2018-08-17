#include <SFML/Network.hpp>
#include "ServerPlayer.hpp"
#include <iostream>
#include <vector>

int main(int, char const**)
{
    //Variables
    int lastID = 20;
    bool serverIsRunning = true;

    //***************************** VECTOR ARRAYS ************************************

    std::vector<ServerPlayer>connectedPlayers;

    //********************* NETWORK *********************************
    sf::Packet packet;
    sf::TcpSocket socket;
    int port = 2241;

    sf::TcpListener listener;
    listener.listen(port);

    //******************************************* MAIN LOOP ****************************************************************************8
    sf::Vector2f receivedPosition;
    int receivedID;

    while(serverIsRunning) {
        packet.clear();
        std::cout << "Player on server: " << connectedPlayers.size() << std::endl;

        if(listener.accept(socket) == sf::Socket::Done) {
            ServerPlayer buff;
            buff.setPlayerPosition(sf::Vector2f(100, 100));
            buff.setUniqueID(lastID);
            lastID++;
            packet << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
            connectedPlayers.push_back(buff);
            socket.send(packet);
            socket.setBlocking(false);
        }

        if(packet && packet >> receivedPosition.x >> receivedPosition.y >> receivedID) {
            for(int i = 0; i < connectedPlayers.size(); i++) {
                if(connectedPlayers[i].getUniqueID() == receivedID) {
                    connectedPlayers[i].setPlayerPosition(receivedPosition);
                }
            }
        }
    }

    return EXIT_SUCCESS;
}