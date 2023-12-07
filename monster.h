#ifndef H_monster
#define H_monster

#include "character_creation.h"
#include <string>

using namespace std;

class monster: public character_creation
{
    public:
        void set_monster_stats(int att, int heal, int resist); 
        void set_monster_type(string m_type);
        void set_monster_attack(int att);
        void set_monster_resistance(int resist);
        int get_attack() const;
        int get_health() const;
        int get_resistance() const;
        string get_monster_type() const;
        void increase_monster_lvl(int att, int heal, int resist);

        void print() const;

        monster();
        monster(int att, int heal, int resist);

    private:
        int attack;
        //int health;
        int resistance; 
        string monster_type;
};

#endif
