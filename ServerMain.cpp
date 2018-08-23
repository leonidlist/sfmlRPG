#include <SFML/Network.hpp>
#include "ServerPlayer.hpp"
#include <iostream>
#include <vector>

enum packetTypes {
    newFirstPlayer, newPlayer, updatePlayer
};

void showConnectedTable(std::map<int, std::string> &ium);

int main(int, char const**)
{
    //Variables
    bool serverIsRunning = true;

    int lastID = 1;
    int playersCounter = 0;

    //***************************** VECTOR ARRAYS ************************************

    std::vector<ServerPlayer>connectedPlayers;

    //********************* MAP IP-UID ****************************

    std::map<int, std::string>ipUIDMap;

    //********************* NETWORK *********************************

    int port = 53000;
    sf::TcpListener listener;
    listener.setBlocking(true);
    sf::TcpSocket socket;
    sf::TcpSocket socket2;
    
    if(listener.listen(port) != sf::TcpListener::Done) {
        std::cout << "Can't start a server." << std::endl;
        return 1;
    }
    std::cout << "Server is listening on port " << port << ", waiting for connections..." << std::endl;
    std::cout << "=====================================" << std::endl;

    if(listener.accept(socket) == sf::Socket::Done) {
        std::cout << "Socket 1 using." << std::endl;
        std::string connectedIP = socket.getRemoteAddress().toString();
        std::cout << "New player just connected from " << connectedIP << std::endl;
        ServerPlayer buff;
        buff.setPlayerPosition(sf::Vector2f(150,150));
        buff.setUniqueID(lastID);
        sf::Packet initPacket;
        if(lastID == 1)
            initPacket << newFirstPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
        else
            initPacket << newPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
        socket.send(initPacket);
        std::cout << "Init packet have been sent." << std::endl;
        connectedPlayers.push_back(buff);
        ipUIDMap.insert(std::pair<int, std::string>(lastID, connectedIP));
        showConnectedTable(ipUIDMap);
        playersCounter++;
        lastID++;
        initPacket.clear();
    }
    if(listener.accept(socket2) == sf::Socket::Done) {
        std::cout << "Socket 2 using." << std::endl;
        std::string connectedIP = socket2.getRemoteAddress().toString();
        std::cout << "New player just connected from " << connectedIP << std::endl;
        ServerPlayer buff;
        buff.setPlayerPosition(sf::Vector2f(150,150));
        buff.setUniqueID(lastID);
        sf::Packet initPacket;
        if(lastID == 1)
            initPacket << newFirstPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
        else
            initPacket << newPlayer << buff.getPlayerPosition().x << buff.getPlayerPosition().y << buff.getUniqueID();
        socket2.send(initPacket);
        std::cout << "Init packet have been sent." << std::endl;
        connectedPlayers.push_back(buff);
        ipUIDMap.insert(std::pair<int, std::string>(lastID, connectedIP));
        showConnectedTable(ipUIDMap);
        playersCounter++;
        lastID++;
        initPacket.clear();
    }

    //******************************************* MAIN LOOP ****************************************************************************8
    sf::Vector2f receivedPosition;
    int receivedID;
    int prev;
    int t;
    sf::Packet packet;
    sf::Packet packet2;

    while(serverIsRunning) {
        socket.receive(packet);
        socket2.receive(packet2);
        int incomingPacketType, uid;
        sf::Vector2f updatePosition;
        if(packet && packet >> incomingPacketType >> updatePosition.x >> updatePosition.y >> uid) {
            std::cout << "IPC: " << incomingPacketType << std::endl;
            if(incomingPacketType == 2) {
                for(auto i = connectedPlayers.begin(); i != connectedPlayers.end(); i++) {
                    if(i->getUniqueID() == uid) {
                        i->setPlayerPosition(updatePosition);
                        std::cout << "Player's coordinates with ID: " << i->getUniqueID() << " was updated to " << updatePosition.x << ":" << updatePosition.y << std::endl;
                    }
                }
            }
        }
        if(packet2 && packet2 >> incomingPacketType >> updatePosition.x >> updatePosition.y >> uid) {
            std::cout << "IPC: " << incomingPacketType << std::endl;
            if(incomingPacketType == 2) {
                for(auto i = connectedPlayers.begin(); i != connectedPlayers.end(); i++) {
                    if(i->getUniqueID() == uid) {
                        i->setPlayerPosition(updatePosition);
                        std::cout << "Player's coordinates with ID: " << i->getUniqueID() << " was updated to " << updatePosition.x << ":" << updatePosition.y << std::endl;
                    }
                }
            }
        }

        // if(packet && packet >> receivedPosition.x >> receivedPosition.y >> receivedID) {
        //     for(int i = 0; i < connectedPlayers.size(); i++) {
        //         if(connectedPlayers[i].getUniqueID() == receivedID) {
        //             connectedPlayers[i].setPlayerPosition(receivedPosition);
        //         }
        //     }
        // }
    }

    return EXIT_SUCCESS;
}

void showConnectedTable(std::map<int, std::string> &ium) {
    std::cout << "=================" << std::endl;
    std::map<int, std::string>::iterator iter;
    for(iter = ium.begin(); iter != ium.end(); iter++) {
        std::cout << "Player ID: " << iter->first << ". Player IP: " << iter->second << std::endl;
    }
    std::cout << "=================" << std::endl;
}