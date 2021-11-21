#include "creature.h"

Creature::Creature(const std::string name,
                   const char col,
                   const int atk,
                   const int mx_hp,
                   const mana cst,
                   std::vector<trait> &vt):
                    Card(CREATURE, name, col),
                    cost(cst), attack(atk),
                    max_health(mx_hp),
                    traits(vt)
{ }


Creature make_Creature(std::string line){
    std::vector<std::string> params = split(line, ',');
    int color = atoi(params[1].c_str());
    mana cost(params[2]);
    int attack = atoi(params[3].c_str());
    int max_health = atoi(params[4].c_str());
    std::vector<trait> vt;
    if(params[5].length() > 0){
        std::vector<std::string> trait_strings = split(params[5],'|');
        vt.resize(trait_strings.size());
        for(unsigned long i=0; i<trait_strings.size(); i++){
            vt[i] = trait(trait_strings[i]);
        }
    }

    return Creature(params[0], color, attack, max_health, cost, vt);
}
