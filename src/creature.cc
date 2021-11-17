#include "creature.h"

Creature::Creature(const std::string name,
                   const char col,
                   const int atk,
                   const int mx_hp,
                   const mana cst):
                    Card(CREATURE, name, col),
                    cost(cst), attack(atk),
                    max_health(mx_hp)
{ }


Creature make_Creature(std::string line){
    std::vector<std::string> params = split(line, ',');
    int color = atoi(params[1].c_str());
    mana cost(params[2]);
    int attack = atoi(params[3].c_str());
    int max_health = atoi(params[4].c_str());

    return Creature(params[0], color, attack, max_health, cost);
}
