#ifndef H_mage
#define H_mage

#include "character_creation.h"

class mage: public character_creation
{
    public:
        void set_stats(int heal, int def, int mp, int m);
        void set_magic_power(int mp); 
        void set_mana(int m);
        void set_mana2(int m);
        void set_health_after_attack(int mag);
        int get_magic_power() const;
        int get_mana() const;
        int get_fireball();
        int get_ice_lance();
        int get_lightning_strike();

        void print() const;

        mage();
        mage(int heal = 10, int def = 1, int mp = 5, int m = 3);

    private:
        int magic_power;
        int mana;
};

#endif
