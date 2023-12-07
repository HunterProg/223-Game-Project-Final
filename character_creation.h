#ifndef H_character_creation
#define H_character_creation

class character_creation
{
    public:
      void set_stats(int heal, int def);
      void set_health(int heal);
      void set_health2(int heal);
      void set_defense(int def);
      int get_health() const;
      int get_defense() const;

      virtual void print() const;

      character_creation();
      character_creation(int heal, int def);

    protected:
      int health;
      int defense;
};

#endif
