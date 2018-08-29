#ifndef RPGSFML_SPELL
#define RPGSFML_SPELL

#include <SFML/System.hpp>

class Spell {
    int spellCoolDown;
    int manaCost;
    int damage;

public:
    bool readyToCast = true;
    Spell():Spell(10, 0, 90){}
    Spell(int cd, int mc, int dmg);

    void setSpellCoolDown(int cd);
    void setManaCost(int mc);
    void setDamage(int dmg);
    int getSpellCoolDown();
    int getManaCost();
    int getDamage();
};
#endif