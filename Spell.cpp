#include "Spell.hpp"

Spell::Spell(int cd, int mc, int dmg) {
    spellCoolDown = cd;
    manaCost = mc;
    damage = dmg;
}

void Spell::setSpellCoolDown(int cd) {
    spellCoolDown = cd;
}

void Spell::setManaCost(int mc) {
    manaCost = mc;
}

void Spell::setDamage(int dmg) {
    damage = dmg;
}

int Spell::getSpellCoolDown() {
    return spellCoolDown;
}

int Spell::getManaCost() {
    return manaCost;
}

int Spell::getDamage() {
    return damage;
}