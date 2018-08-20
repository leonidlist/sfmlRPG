#include <SFML/Network.hpp>
#include "ServerPlayer.hpp"
#include <iostream>
#include <vector>

enum packetTypes {
    newFirstPlayer, newPlayer, updatePlayer
};

void showConnectedTable(std::map<std::string, int> &ium);

int main(int, char const**)
{
    //Variables
    int lastID = 1;
    bool serverIsRunning = true;
    int playersCounter = 0;

    //***************************** VECTOR ARRAYS ************************************

    std::vector<ServerPlayer>connectedPlayers;

    //********************* MAP IP-UID ****************************

    std::map<std::string, int>ipUIDMap;

    //********************* NETWORK *********************************
    sf::Packet packet;
    sf::TcpSocket socket;
    int port = 2241;

    sf::TcpListener listener;
    listener.listen(port);

    //******************************************* MAIN LOOP ****************************************************************************8
    sf::Vector2f receivedPosition;
    int receivedID;
    int prev;

    while(serverIsRunning) {
        packet.clear();

        if(listener.accept(socket) == sf::Socket::Done && playersCounter == 0) {
            //Get ip address & get packet type
            std::cout << "PACKET type: 0" << std::endl;
            std::string remoteIP = socket.getRemoteAddress().toString();
            //New player initialization
            ServerPlayer buff;
            buff.setPlayerPosition(sf::Vector2f(100, 100));
            buff.setUniqueID(lastID);
            packet << newFirstPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
            socket.send(packet);
            //Add to server players.
            connectedPlayers.push_back(buff);
            ipUIDMap.insert(std::pair<std::string, int>(remoteIP, buff.getUniqueID()));
            //Increase counters
            lastID++;
            playersCounter++;
            showConnectedTable(ipUIDMap);
        }

        if(listener.accept(socket) == sf::Socket::Done && playersCounter > 0) {
            //Get ip address & get packet type
            std::cout << "PACKET type: 1" << std::endl;
            std::string remoteIP = socket.getRemoteAddress().toString();
            //New player initialization
            ServerPlayer buff;
            buff.setPlayerPosition(sf::Vector2f(100, 100));
            buff.setUniqueID(lastID);
            packet << newPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
            socket.send(packet);
            //Add to server players
            connectedPlayers.push_back(buff);
            ipUIDMap.insert(std::pair<std::string, int>(remoteIP, buff.getUniqueID()));
            //Increase counters
            playersCounter++;
            lastID++;
            showConnectedTable(ipUIDMap);
            // for(int i = 0; i < playersCounter; i++) {
            //     packet.clear();
            //     packet << newPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
            //     socket.send(packet);
            // }
            // socket.setBlocking(false);
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

void showConnectedTable(std::map<std::string, int> &ium) {
    std::cout << "=================" << std::endl;
    std::map<std::string, int>::iterator iter;
    for(iter = ium.begin(); iter != ium.end(); iter++) {
        std::cout << iter->first << " : " << iter->second << std::endl;
    }
    std::cout << "=================" << std::endl;
}