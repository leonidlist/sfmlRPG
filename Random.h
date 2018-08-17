//
// Created by leonid on 25.07.18.
//

#ifndef RPGSFML_RANDOM_H
#define RPGSFML_RANDOM_H

#include "stdio.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <tgmath.h>
#include <deque>
#include <list>
#include <vector>
#include <unistd.h>

int generateRandom(int max);
int generateRandom0(int max);
bool generateRandomBool();

#endif //RPGSFML_RANDOM_H
