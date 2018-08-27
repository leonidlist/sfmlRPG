#ifndef RPGSFML_ROOM
#define RPGSFML_ROOM

#include "Wall.hpp"
#include <vector>

class Room {
public:
    int startX, startY, endX, endY; //In coordinates

    int width; //In blocks
    int height; //In blocks
    int squareArea;

    int doorSide; //1 - up, 2 - down, 3 - left, 4 - right
    int doorPos;

    Room(int startX, int startY, std::vector<Wall> &arr);
    Room(int startX, int startY, int width, int height, int doorSide, int doorPos, std::vector<Wall> &arr, sf::Texture &wallTexture, sf::Texture &boxTexture);
};

#endif