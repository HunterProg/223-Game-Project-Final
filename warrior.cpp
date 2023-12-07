#include <iostream>
#include "character_creation.h"
#include "warrior.h"

using namespace std;

void warrior::set_stats(int heal, int def, int att, int stam)
{
    character_creation::set_stats(heal, def);

    attack = att;
    stamina = stam;
}

void warrior::set_attack(int att)
{
    attack = attack + att;
}

void warrior::set_stamina(int stam)
{
    stamina = stamina + stam;
}

void warrior::set_stamina2(int stam)
{
    stamina = stam;
}

void warrior::set_health_after_attack(int att)
{
    health = health - att;
}

int warrior::get_attack() const
{
    return attack;
}

int warrior::get_stamina() const
{
    return stamina;
}

int warrior::get_slash()
{
    stamina = stamina - 1;
    return attack;
}

int warrior::get_bludgeon()
{
    stamina = stamina - 1;
    return attack;
}

int warrior::get_crush()
{
    stamina = stamina - 3;
    return attack;
}

void warrior::print() const
{
    character_creation::print();
    cout << "Defense: " << get_defense() << endl;
    cout << "Attack: " << attack << endl;
    cout << "Stamina: " << stamina << endl;
}

warrior::warrior()
{
    attack = 2;
    stamina = 5;
}

warrior::warrior(int heal, int def, int att, int stam)
        :character_creation(heal, def)
{
    attack = att;
    stamina = stam;
}
