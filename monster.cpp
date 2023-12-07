#include <iostream>
#include <string>
#include "character_creation.h"
#include "monster.h"

using namespace std;

void monster::set_monster_stats(int att, int heal, int resist)
{
    attack = att;
    health = heal;
    resistance = resist;
}

void monster::set_monster_type(string m_type)
{
    monster_type = m_type;
}

void monster::set_monster_attack(int att)
{
    attack = att;
}

void monster::set_monster_resistance(int resist)
{
    resistance = resist;
}

int monster::get_attack() const
{
    return attack;
}

int monster::get_health() const
{
    return health;
}

int monster::get_resistance() const
{
    return resistance;
}

string monster::get_monster_type() const
{
    return monster_type;
}

void monster::increase_monster_lvl(int att, int heal, int resist)
{
    static int at = att;
    at = at + at;

    static int h = heal;
    h = h + h;

    static int res = resist;
    res = res + res;
    
    attack = attack + at;
    health = health + h;
    resistance = resistance + res;
}

void monster::print() const
{
    cout << "Attack: " << attack << endl;
    character_creation::print();
    cout << "Monster Type: " << monster_type << endl;
}

monster::monster()
{
    attack = 3;
    health = 20;
    resistance = 5;
    monster_type = "none";
}
  
monster::monster(int att, int heal, int resist)
{
    attack = att;
    health = heal;
    resistance = resist;
}
