#ifndef H_warrior
#define H_warrior

#include "character_creation.h"

class warrior: public character_creation
{
    public:
        void set_stats(int heal, int def, int att, int stam);
        void set_attack(int att); 
        void set_stamina(int stam);
        void set_stamina2(int stam);
        void set_health_after_attack(int att);
        int get_attack() const;
        int get_stamina() const;
        int get_slash();
        int get_bludgeon();
        int get_crush();

        void print() const;

        warrior();
        warrior(int heal = 10, int def = 2, int att = 2, int stam = 5);

    private:
        int attack;
        int stamina;
};

#endif
