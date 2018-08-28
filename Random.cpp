#include "Random.hpp"

int generateRandom(int max) {
    return rand() % (max-1) + 1;
}

int generateRandom0(int max) {
    return rand() % max;
}

bool generateRandomBool() {
    return rand() % 1;
}