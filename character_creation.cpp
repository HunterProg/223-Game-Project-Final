#include <iostream>
#include "character_creation.h"

using namespace std;

void character_creation::set_stats(int heal, int def)
{
    health = heal;
    defense = def;
}

void character_creation::set_health(int heal)
{
    health = health + heal;
}

void character_creation::set_health2(int heal)
{
    health = heal;
}

void character_creation::set_defense(int def)
{
    defense = defense + def;
}

int character_creation::get_health() const
{
    return health;
}

int character_creation::get_defense() const
{
    return defense;
}

void character_creation::print() const
{
    cout << "Health: " << health << endl;
}

character_creation::character_creation()
{
    health = 10;
    defense = 2;
}

character_creation::character_creation(int heal, int def)
{
    health = heal;
    defense = def;
}
