//
// Created by leonid on 25.07.18.
//

#include "Random.h"

int generateRandom(int max) {
    return std::rand() % (max-1) + 1;
}

int generateRandom0(int max) {
    return std::rand() % max;
}

bool generateRandomBool() {
    return std::rand() % 1;
}