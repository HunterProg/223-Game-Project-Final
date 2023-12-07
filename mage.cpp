#include <iostream>
#include "character_creation.h"
#include "mage.h"

using namespace std;

void mage::set_stats(int heal, int def, int mp, int m)
{
    character_creation::set_stats(heal, def);

    magic_power = mp;
    mana = m;
}

void mage::set_magic_power(int mp)
{
    magic_power = magic_power + mp;
}

void mage::set_mana(int m)
{
    mana = mana + m;
}

void mage::set_mana2(int m)
{
    mana = m;
}

void mage::set_health_after_attack(int mag)
{
    health = health - mag;
}

int mage::get_magic_power() const
{
    return magic_power;
}

int mage::get_mana() const
{
    return mana;
}

int mage::get_fireball()
{
    mana = mana - 1;
    return magic_power;
}

int mage::get_ice_lance()
{
    mana = mana - 1;
    return magic_power;
}

int mage::get_lightning_strike()
{
    mana = mana - 3;
    return magic_power;
}

void mage::print() const
{
    character_creation::print();
    cout << "Defense: " << get_defense() << endl;
    cout << "Magic Power: " << magic_power << endl;
    cout << "Mana: " << mana << endl;
}

mage::mage()
{
    magic_power = 5;
    mana = 3;
}
  
mage::mage(int heal, int def, int mp, int m)
     :character_creation(heal, def)
{
    magic_power = mp;
    mana = m;
}
