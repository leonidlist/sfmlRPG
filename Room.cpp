#include "Room.h"
#include "Wall.h"

Room::Room(int startX, int startY, std::vector<Wall> &arr) {
    this->startX = startX;
    this->startY = startY;
    std::srand(std::time(NULL));
    width = rand() % 4 + 5;
    height = rand() % 4 + 5;

    doorSide = rand() % 4 + 1;
    if(doorSide == 1 || doorSide == 2)
        doorPos = rand() % width + 1;
    else
        doorPos = rand() % (height-1) + 1;

    Wall wall1;

    endX = this->startX + width*wall1.props;
    endY = this->startY + height*wall1.props;

    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Door generated at side: " << doorSide << std::endl;
    std::cout << "Door generated at pos: " << doorPos << std::endl;

    //Top wall
    for(int i = 0; i < width; i++) {
        if(doorSide == 1 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(startX+(i*wall1.props), startY);
        arr.push_back(wall1);
    }
    //Bottom wall
    for(int i = 0; i < width+1; i++) {
        if(doorSide == 2 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(startX+(i*wall1.props), endY);
        arr.push_back(wall1);
    }
    //Left wall
    for(int i = 0; i < height; i++) {
        if(doorSide == 3 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(startX, startY+(i*wall1.props));
        arr.push_back(wall1);
    }
    //Right wall
    for(int i = 0; i < height; i++) {
        if(doorSide == 4 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(endX, startY+(i*wall1.props));
        arr.push_back(wall1);
    }
}

Room::Room(int startX, int startY, int width, int height, int doorSide, int doorPos, std::vector<Wall> &arr, sf::Texture &wallTexture, sf::Texture &boxTexture) {
    this->startX = startX;
    this->startY = startY;
    this->width = width;
    this->height = height;
    this->doorSide = doorSide;
    this->doorPos = doorPos;
    Wall wall1;
    wall1.destructable = false;
    wall1.sprite.setTexture(wallTexture);
    endX = this->startX + width*wall1.props;
    endY = this->startY + height*wall1.props;

    for(int i = 0; i < width; i++) {
        if(doorSide == 1 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(startX+(i*wall1.props), startY);
        wall1.sprite.setPosition(wall1.rect.getPosition());
        arr.push_back(wall1);
    }
    //Bottom wall
    for(int i = 0; i < width+1; i++) {
        if(doorSide == 2 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(startX+(i*wall1.props), endY);
        wall1.sprite.setPosition(wall1.rect.getPosition());
        arr.push_back(wall1);
    }
    //Left wall
    for(int i = 0; i < height; i++) {
        if(doorSide == 3 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(startX, startY+(i*wall1.props));
        wall1.sprite.setPosition(wall1.rect.getPosition());
        arr.push_back(wall1);
    }
    //Right wall
    for(int i = 0; i < height; i++) {
        if(doorSide == 4 && doorPos == i) {
            continue;
        }
        wall1.rect.setPosition(endX, startY+(i*wall1.props));
        wall1.sprite.setPosition(wall1.rect.getPosition());
        arr.push_back(wall1);
    }

    int amountOfBoxes = std::rand() % 5 + 1;
    wall1.sprite.setTexture(boxTexture);
    wall1.destructable = true;
    for(int i = 0; i < amountOfBoxes; i++) {
        int randX = std::rand() % (endX-startX-140) + startX+70;
        int randY = std::rand() % (endY-startY-140) + startY+70;
        wall1.rect.setPosition(randX, randY);
        wall1.sprite.setPosition(wall1.rect.getPosition());
        arr.push_back(wall1);
    }
}