#ifndef RPGSFML_VECTORS
#define RPGSFML_VECTORS

#include <vector>
#include "Powerup.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Wall.h"
#include "TextDisplay.h"
#include "Heal.h"
#include "Room.h"

class Vectors {
    std::vector<Powerup> powerupVector;
    std::vector<Projectile> projectileVector;
    std::vector<Enemy> enemyVector;
    std::vector<Pickup> pickupVector;
    std::vector<Wall> wallVector;
    std::vector<TextDisplay> textDisplayVector;
    std::vector<Heal> healVector;
    std::vector<Room> roomVector;
public:
    Vectors();
    std::vector<Powerup>& getPowerupVector();
    std::vector<Projectile>& getProjectileVector();
    std::vector<Enemy>& getEnemyVector();
    std::vector<Pickup>& getPickupVector();
    std::vector<Wall>& getWallVector();
    std::vector<TextDisplay>& getTextDisplayVector();
    std::vector<Heal>& getHealVector();
    std::vector<Room>& getRoomVector();
};

#endif