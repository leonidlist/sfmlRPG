#include "Random.hpp"

int generateRandom(int max) {
    return std::rand() % (max-1) + 1;
}

int generateRandom0(int max) {
    return std::rand() % max;
}

bool generateRandomBool() {
    return std::rand() % 1;
}