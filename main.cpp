#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "character_creation.h"
#include "warrior.h"
#include "mage.h"
#include "monster.h"
#include "invalid_choice.h"

using namespace std;

string character_creation_menu();
void call_stats(character_creation& i);
void stat_menu_selection(string u_class);
int stat_assigned(int s_amt, int& total_stats);
void class_stat_menu(character_creation& i, warrior &temp_w, mage &temp_m, string u_class, string diff);
string select_difficulty(string& cheat_code);
void generate_monsters_off_difficulty(monster monsters[], string diff, int num);
string monster_type_selection();
string monster_type_hard();
int attack_menu(string u_class);
void helpful_information();
void game_menu(warrior& user_w, mage& user_m, string u_class, monster monsters[], int num, string difficulty, int starting_stam, int starting_m);
void game(warrior user_w, mage user_m, monster monsters[], int num, string u_class, string diff);

int main() 
{
    string user_class;
    string cheat;
    warrior temp_warrior(15, 2, 2, 10);
    mage temp_mage(15, 1, 5, 8);
    warrior temp_cheat_warrior(999, 999, 999, 999);
    mage temp_cheat_mage(999, 999, 999, 999);
    string difficulty;

    warrior user_warrior(1, 1, 1, 1);
    mage user_mage(1, 1, 1, 1);

    difficulty = select_difficulty(cheat);

    int num_monsters;
  
    if(difficulty == "Easy" || difficulty == "easy")
        num_monsters = 3;
    if(difficulty == "Medium" || difficulty == "medium")
        num_monsters = 4;
    if(difficulty == "Hard" || difficulty == "hard")
        num_monsters = 5;
    
    monster monsters[num_monsters];
      
    generate_monsters_off_difficulty(monsters, difficulty, num_monsters);

    user_class = character_creation_menu();

    if (user_class == "warrior" || user_class == "Warrior")
    {
        cout << endl << endl;
        cout << "You chose the Warrior Class." << endl;
        cout << "Current Stats: " << endl;
        call_stats(temp_warrior);
        cout << endl;
        class_stat_menu(temp_warrior, temp_warrior, temp_mage, user_class, difficulty);

        cout << "Your Final Stats: " << endl;
        user_warrior = temp_warrior;
        call_stats(user_warrior);

    }
    else
    {
        cout << endl << endl;
        cout << "You chose the Mage Class." << endl;
        cout << "Current Stats: " << endl;
        call_stats(temp_mage);
        cout << endl;
        class_stat_menu(temp_mage, temp_warrior, temp_mage, user_class, difficulty);

        cout << "Your Final Stats: " << endl;
        user_mage = temp_mage;
        call_stats(user_mage);
    }

    if(cheat == "EX" && (user_class == "warrior" || user_class == "Warrior"))
    {
        cout << endl << endl;
        cout << "You have entered the cheat code, generating new character." << endl << endl;
        user_warrior = temp_cheat_warrior;
        cout << "New Stats: " << endl;
        user_warrior.print();
    }
    else if(cheat == "EX" && (user_class == "Mage" || user_class == "mage"))
    {
        cout << endl << endl;
        cout << "You have entered the cheat code, generating new character." << endl << endl;
        user_mage = temp_cheat_mage;
        cout << "New Stats: " << endl;
        user_mage.print();
    }
      
    game(user_warrior, user_mage, monsters, num_monsters, user_class, difficulty);
    return 0;
}

string character_creation_menu()
{//User chooses the specific class they want to play
    string choice = "";
    bool done = false;
    char trash;
  
    cin.get(trash);
    
    cout << "Choose a class between Warrior or Mage: ";
    getline(cin, choice);
      
    do
    {
        try
        {  
            if(choice == "Warrior" || choice == "warrior" || choice == "Mage" || choice == "mage")
            {
                done = true;
                return choice;
            }
            else
                throw invalid_choice("Must be Warrior or Mage.");
        }
        catch (invalid_choice err)
        {
            cout << endl;
            cout << err.what() << endl;
            cout << "Choose a class between Warrior or Mage: ";
            getline(cin, choice);
        }
    }while(!done);
    
    return "Failed";
}

void call_stats(character_creation& i)
{//Calls the stats of the respective class (Warrior or Mage)
    i.print();
}

void stat_menu_selection(string u_class)
{//Shows what the user can do during stat allocation based on class chosen
    cout << "1. Current Stats." << endl;
    cout << "2. Health." << endl;
    cout << "3. Defense." << endl;
    if(u_class == "Warrior" || u_class == "warrior")
    {  
        cout << "4. Attack." << endl;
        cout << "5. Stamina." << endl;
    }
    else if(u_class == "Mage" || u_class == "mage")
    {
        cout << "4. Magic Power." << endl;
        cout << "5. Mana." << endl;
    }
    cout << "6. Reset stats to base." << endl;
    cout << "7. Confirm Selection?" << endl;
}

int stat_assigned(int s_amt, int& total_stats)
{//Checks total stats and gets the value of what stat to increase
    try
    {
        if(total_stats == 0)
        {
            cout << "You have " << total_stats << " stat points to spend." << endl << endl;
            return 0;
        }

        cout << "You have " << total_stats << " stat points to spend." << endl;
        cout << "How many points would you like to add? " << endl;
        cin >> s_amt;
        cout << endl;

        if(s_amt < 0)
            throw invalid_choice();
        else if(s_amt > total_stats)
            throw s_amt;

          total_stats = total_stats - s_amt;
        return s_amt;
    }
    catch(invalid_choice err)
    {
        cout << err.what() << endl;
    }
    catch(int err)
    {
        cout << "You only have " << total_stats << " stat points." << endl << endl;
    }

    return 0;
}

void class_stat_menu(character_creation& i, warrior &temp_w, mage &temp_m, string u_class, string diff)
{//Shows the stat menu and allows user to allocate their stats
    int designated_stat;
    int stat_amount = 0;
    char choice;
    static int t_stats;

    if(diff == "Easy" || diff == "easy")
        t_stats = 10;
    if(diff == "Medium" || diff == "medium")
        t_stats = 13;
    if(diff == "Hard" || diff == "hard")
        t_stats = 15;

    do
    {
        try
        {
          cout << "Select the name of the stat you wish to increase or confirm current stats." << endl;
          stat_menu_selection(u_class);
          cin >> designated_stat;
          cout << endl;

          if (designated_stat < 1 || designated_stat > 7)
              throw invalid_choice("Selection must be between 1 and 7.");

          //User selects from the stat_menu_selection which stat to increase
          switch(designated_stat)
          {
            case 1:
              cout << "Current Stats:" << endl;
              call_stats(i);
              cout << endl;
              break;
            case 2:
              cout << "Current Health: " << i.get_health() << endl << endl;

              i.set_health(stat_assigned(stat_amount, t_stats));
              break;
            case 3:
              cout << "Current Defense: " << i.get_defense() << endl << endl;

              i.set_defense(stat_assigned(stat_amount, t_stats));
              break;
            case 4:
              if (u_class == "warrior" || u_class == "Warrior")
              { 
                  cout << "Current Attack: " << temp_w.get_attack() << endl << endl;
                
                  temp_w.set_attack(stat_assigned(stat_amount, t_stats));
              }
              else if (u_class == "mage" || u_class == "Mage")
              {
                  cout << "Current Magic Power: " << temp_m.get_magic_power() << endl << endl;
                
                  temp_m.set_magic_power(stat_assigned(stat_amount, t_stats));
              }
              break;
            case 5:
              if (u_class == "warrior" || u_class == "Warrior")
              { 
                  cout << "Current Stamina: " << temp_w.get_stamina() << endl << endl;
                
                  temp_w.set_stamina(stat_assigned(stat_amount, t_stats));
              }
              else if (u_class == "mage" || u_class == "Mage")
              {
                  cout << "Current Mana: " << temp_m.get_mana() << endl << endl;
                
                  temp_m.set_mana(stat_assigned(stat_amount, t_stats));
              }
              break;
            case 6://Resets the stats of specified class
              if (u_class == "warrior" || u_class == "Warrior")
                  temp_w.set_stats(15, 2, 2, 10);
              else if (u_class == "mage" || u_class == "Mage")
                  temp_m.set_stats(15, 1, 5, 8);  
              cout << "Stats have been reset to base." << endl << endl;
              if(diff == "Easy" || diff == "easy")
                  t_stats = 10;
              if(diff == "Medium" || diff == "medium")
                  t_stats = 15;
              if(diff == "Hard" || diff == "hard")
                  t_stats = 20;
              break;
            default:
              cout << "Are you sure you want your current stats? Y/N" << endl;
              cin >> choice;
              cout << endl;

              if(choice == 'Y' || choice == 'y')
              {
                  cout << "Stats have been saved!" << endl << endl;
                  break;
              }
              else if(choice == 'N' || choice == 'n')
                  break;
              else 
                  throw invalid_choice("Invalid selection, please enter Y for yes or N for no.");
          }
        }
        catch (invalid_choice err)
        {
            cout << err.what() << endl;
        }
    }while(designated_stat != 7);
}

string select_difficulty(string& cheat_code)
{//Selects the difficulty of the game to use for player stats/monster generation
    string difficulty;
    bool done = false;

    do
    {
        try
        {
            cout << "Welcome to Dungeon Adventures!" << endl << endl;
  
            cout << "Enter a difficulty level: Easy, Medium, or Hard." << endl;
            cin >> difficulty;
            cout << endl;

            if(difficulty == "EX")
            {
                cheat_code = difficulty;
                difficulty = "Hard";
            }
  
            if(difficulty != "Easy" && difficulty != "Medium" && difficulty != "Hard")  
              if(difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
                  throw invalid_choice("Invalid difficulty level.");
  
            cout << "Difficulty Selected: " << difficulty << "." << endl;
            cout << "Generating Monsters." << endl << endl;
  
          done = true;
            return difficulty;
        }
        catch(invalid_choice err)
        {
            cout << err.what() << endl << endl;
        }
    }while(!done);
    return "Failure";
}

void generate_monsters_off_difficulty(monster monsters[], string diff, int num)
{//Generates the amount and stats of monsters based on the difficulty selected

    int monster_stat1; //attack
    int monster_stat2; //health
    int monster_stat3; //type

    for(int i = 1; i < num; i++)
    {
        if(num == 3)
        {
            monster_stat1 = 5;
            monster_stat2 = 10;
            monster_stat3 = 3;
            monsters[0].set_monster_stats(monster_stat1, monster_stat2, monster_stat3);
            monsters[i].set_monster_stats(monster_stat1, monster_stat2, monster_stat3);
            monsters[i].increase_monster_lvl(1, 2, 1);
            monsters[i].set_monster_type("Weak");
        }
        if(num == 4)
        {
            monster_stat1 = 6;
            monster_stat2 = 15;
            monster_stat3 = 5;
            monsters[0].set_monster_stats(monster_stat1, monster_stat2, monster_stat3);
            monsters[i].set_monster_stats(monster_stat1, monster_stat2, monster_stat3);
            monsters[i].increase_monster_lvl(1, 2, 1);
            monsters[i].set_monster_type(monster_type_selection());
        }

        if(num == 5)
        {
            monster_stat1 = 7;
            monster_stat2 = 15;
            monster_stat3 = 7;
            monsters[0].set_monster_stats(monster_stat1, monster_stat2, monster_stat3);
            monsters[i].set_monster_stats(monster_stat1, monster_stat2, monster_stat3);
            monsters[i].increase_monster_lvl(1, 2, 1);
            monsters[i].set_monster_type(monster_type_hard());

        }
    }
    if(num == 3)
    {
        monsters[0].set_monster_type("Weak");
    }
    if(num == 4)
    {
        monsters[0].set_monster_type(monster_type_selection());
        monsters[3].set_health2(27);
    }
    if(num == 5)
    {
        monsters[0].set_monster_type(monster_type_hard());
        monsters[3].set_health2(25);
        monsters[4].set_monster_attack(18);
        monsters[4].set_health2(30);
        monsters[4].set_monster_resistance(18);
    }
}

string monster_type_selection()
{//Returns monster type after random num between 1 and 2
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(1, 2);
    int random_number = dist(gen);
    //These lines of code above are part of the random header which
    //according to google is a more advance random num generator option

    if(random_number == 1)
      return "Plant";
    if(random_number == 2)
      return "Water";

  return "Error Type";
}

string monster_type_hard()
{//Returns hard difficulty monster type after random num between 0 and 1
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(0, 1);
    int hard_number = dist(gen);

    if(hard_number == 1)
      return "Metal";
    else
      return "None";

  return "Error Type Hard";
}

int attack_menu(string u_class)
{//Dictates the type of menu shown and the attacks they can do
  bool done = false;
  int choice;
  
  do
  {
      try
      {
          cout << "Which attack would you like to do?" << endl;
      
          if(u_class == "Warrior" || u_class == "warrior")
          {
              cout << "1. Slash." << endl;
              cout << "2. Bludgeon" << endl;
              cout << "3. Crush" << endl;
          }
          else if(u_class == "Mage" || u_class == "mage")
          {
              cout << "1. Fireball." << endl;
              cout << "2. Ice Lance." << endl;
              cout << "3. Lightning Strike." << endl;
          }

          cin >> choice;
          cout << endl;

          if(!cin)
            throw invalid_choice("Enter an integer");
          else if(choice < 1 || choice > 3)
            throw invalid_choice("Number has to be between 1 and 3");

          done = true;
          return choice;
      }
      catch(invalid_choice err)
      {
          cout << err.what() << endl;
      }
  }while(!done);

  return 0;
}

void helpful_information()
{//Provides helpful information to the player
    cout << endl;
    cout << "The monsters will attack only after you do, so it's recommended to attack even if you have 1 health." << endl;
    cout << "Upon defeating a monster you will regain all your health." << endl;
    cout << "Certain monster's are weaker against certain attacks depending on their type." << endl;
    cout << "Defending recovers your stamina so it's recommended to defend if you are low." << endl;
}

void game_menu(warrior& user_w, mage& user_m, string u_class, monster monsters[], int num, string difficulty, int starting_stam, int starting_m)
{//This dictates the gameplay of the game based on user actions
    int choice;
    int second_choice;
    char third_choice;
    int health_potion;
    int temp_place_holder = 0;

    character_creation* j = nullptr;

    if (u_class == "warrior" || u_class == "Warrior")
        j = &user_w;
    else if (u_class == "mage" || u_class == "Mage")
        j = &user_m;

    int starting_health = j->get_health();
  
    if(difficulty == "Medium" || difficulty == "medium")
        health_potion = 1;
    if(difficulty == "Hard" || difficulty == "hard")
        health_potion = 2;

    cout << "You have encountered a monster!" << endl << endl;

    cout << "Monster " << num + 1 << endl;
    monsters[num].print();
    cout << endl << endl;

    cout << "Your stats." << endl;
    j->print();

    cout << endl << endl;
    
    while(monsters[num].get_health() > 0 && j->get_health() > 0)
    {    
        cout << "What action would you like to take?" << endl << endl;

        cout << "1. Attack." << endl;
        cout << "2. Defend." << endl;
        cout << "3. Health Potion." << endl;
        cout << "4. Information Guide" << endl;
        
        cin >> choice;
        cout << endl;

        switch(choice)
        {
          case 1:
          //Attacks the monster based on choice and type and monster attacks back based on defense
            second_choice = attack_menu(u_class);
            cout << "You have attacked the monster" << endl << endl;
            try
            {
                if(u_class == "Warrior" || u_class == "warrior")
                {
                  if(dynamic_cast<warrior*>(j)->get_stamina() == 0)
                    throw invalid_choice("You have no stamina left, select a different option.");
                  else if(dynamic_cast<warrior*>(j)->get_stamina() < 3 && second_choice == 3)
                    throw invalid_choice("You have no stamina left, select a different option.");
                }
                else if(u_class == "Mage" || u_class == "mage")
                {
                  if(dynamic_cast<mage*>(j)->get_mana() == 0)
                    throw invalid_choice("You have no stamina left, select a different option.");
                  else if(dynamic_cast<mage*>(j)->get_mana() < 3 && second_choice == 3)
                    throw invalid_choice("You have no mana left, select a different option.");
                }
                  
                if(second_choice == 1)
                {//If attack type one
                  if(u_class == "Warrior" || u_class == "warrior")
                  {
                    if(monsters[num].get_monster_type() == "Weak" || monsters[num].get_monster_type() == "Plant")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_slash()));
                    else if(monsters[num].get_monster_type() == "None" || monsters[num].get_monster_type() == "Metal")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_slash() / 2));
                  }
                  else if(u_class == "Mage" || u_class == "mage")
                  {
                    if(monsters[num].get_monster_type() == "Weak" || monsters[num].get_monster_type() == "Plant")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_fireball()));
                    else if(monsters[num].get_monster_type() == "None" || monsters[num].get_monster_type() == "Metal")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_fireball() / 2));
                  }
                }
                else if(second_choice == 2)
                {//if attack type 2
                  if(u_class == "Warrior" || u_class == "warrior")
                  {
                    if(monsters[num].get_monster_type() == "Weak" || monsters[num].get_monster_type() == "Water")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_bludgeon()));
                    else if(monsters[num].get_monster_type() == "None" || monsters[num].get_monster_type() == "Metal")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_bludgeon() / 2));
                  }
                  else if(u_class == "Mage" || u_class == "mage")
                  {
                    if(monsters[num].get_monster_type() == "Weak" || monsters[num].get_monster_type() == "Water")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_ice_lance()));
                    else if(monsters[num].get_monster_type() == "None" || monsters[num].get_monster_type() == "Metal")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_ice_lance() / 2));
                  }
                }
                else if(second_choice == 3)
                {//if attack type 3
                  if(u_class == "Warrior" || u_class == "warrior")
                  {
                    if(monsters[num].get_monster_type() == "Weak" || monsters[num].get_monster_type() == "Metal")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_crush()));
                    else if(monsters[num].get_monster_type() == "None")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_crush() / 2));
                    else
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<warrior*>(j)->get_crush()));
                  }
                  else if(u_class == "Mage" || u_class == "mage")
                  {
                    if(monsters[num].get_monster_type() == "Weak" || monsters[num].get_monster_type() == "Metal")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_lightning_strike()));
                    else if(monsters[num].get_monster_type() == "None")
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_lightning_strike() / 2));
                    else
                        monsters[num].set_health2(monsters[num].get_health() - (dynamic_cast<mage*>(j)->get_lightning_strike()));
                  }
                }

                if(monsters[num].get_health() <= 0)
                {
                    cout << "You defeated the monster!" << endl << endl;
                    break;
                }
                else if (j->get_health() <= 0)
                {
                    cout << "You have been defeated!" << endl << endl;
                    break;
                }

                //Below has the monster attacking back based on your defense
                if(j->get_defense() < 3 && u_class == "Warrior" || u_class == "warrior")
                    dynamic_cast<warrior*>(j)->set_health_after_attack(monsters[num].get_attack());
                else if(j->get_defense() < 3 && u_class == "Mage" || u_class == "mage")
                    dynamic_cast<mage*>(j)->set_health_after_attack(monsters[num].get_attack());
                else if(j->get_defense() >= 5 && u_class == "Warrior" || u_class == "warrior")
                    dynamic_cast<warrior*>(j)->set_health_after_attack(monsters[num].get_attack() / 2);
                else if(j->get_defense() >= 5 && u_class == "Mage" || u_class == "mage")
                    dynamic_cast<mage*>(j)->set_health_after_attack(monsters[num].get_attack() / 2);
            }
            catch(invalid_choice err)
            {
                cout << err.what() << endl;
            }
            break;
          case 2:
          //Defend to regain stamina/mana and take one damage
            cout << "You have chosen to defend yourself, you take 1 point of damage." << endl << endl;
            if(u_class == "Warrior" || u_class == "warrior")
            {
                dynamic_cast<warrior*>(j)->set_health_after_attack(1);
                temp_place_holder = 5 + dynamic_cast<warrior*>(j)->get_stamina();
                if(temp_place_holder > starting_stam)
                    dynamic_cast<warrior*>(j)->set_stamina2(starting_stam);
                else
                    dynamic_cast<warrior*>(j)->set_stamina(5);
            }
            else
            {
                dynamic_cast<mage*>(j)->set_health_after_attack(1);
                temp_place_holder = 5 + dynamic_cast<mage*>(j)->get_mana();
                if(temp_place_holder > starting_m)
                      dynamic_cast<mage*>(j)->set_mana2(starting_m);
                  else
                      dynamic_cast<mage*>(j)->set_mana(5);
            }
            break;
          case 3:
          //Heals the user based on remaining health and their difficulty
            if(difficulty == "Easy" || difficulty == "easy")
                cout << "No health potions available." << endl << endl;
            if(difficulty == "Medium" || difficulty == "medium")
                cout << health_potion << " health potion available." << endl << endl;
            else 
                cout << health_potion << " health potion available." << endl << endl;

            cout << "Use health potion? (Y/N)" << endl;
            cout << "Current Health: " << j->get_health() << endl;
            cin >> third_choice;
            cout << endl;

            try
            {
                if(third_choice == 'Y' || third_choice == 'y')
                {
                  if(j->get_health() + 5 <= starting_health)
                  {
                      j->set_health(5);
                      health_potion--;
                      break;
                  }
                  else if(j->get_health() + 5 > starting_health)
                  {
                      j->set_health2(starting_health);
                      health_potion--;
                      break;
                  }
                }
                else if(third_choice == 'N' || third_choice == 'n')
                    break;
                else
                    throw invalid_choice("Incorrect Choice.");
            }
            catch(invalid_choice err)
            {
                cout << err.what() << endl << endl;
            }
            break;
          case 4:
            helpful_information();
            cout << endl << endl;
            break;
        }//End of switch

        if(monsters[num].get_health() <= 0 || j->get_health() <= 0)
            break;//Checks user or monster health to see if either are dead to exit loop
      
        cout << "Monster " << num + 1 << endl;
        monsters[num].print();
        cout << endl << endl;
  
        cout << "Your stats." << endl;
        j->print();
  
        cout << endl << endl;
    }//End of while
  if(j->get_health() > 0)
      j->set_health2(starting_health);
  else
      cout << "You have been defeated!" << endl << endl;
}//End of function

void game(warrior user_w, mage user_m, monster monsters[], int num, string u_class, string diff)
{//Makes the game run by calling the game_menu function
    cout << endl << endl;
    int starting_stam = user_w.get_stamina();
    int starting_m = user_m.get_mana();
    cout << "You have begun your quest to defeat the monsters within the dungeon." << endl << endl;
  
    for(int i = 0 ; i < num ; i++)
    {
        if(user_w.get_health() > 0 && user_m.get_health() > 0)
            game_menu(user_w, user_m, u_class, monsters, i, diff, starting_stam, starting_m);
        else
            break;
    }  

    if(user_w.get_health() > 0 && user_m.get_health() > 0)
      cout << "Congratulations! You have defeated all the monsters and won the game!" << endl;
    else
      cout << "You have lost the game." << endl;
}
