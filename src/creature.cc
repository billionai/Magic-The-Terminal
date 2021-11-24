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


Creature make_Creature(std::string line,
                       std::unordered_map<std::string, Effect> m){
    std::vector<std::string> params = split(line, ',');
    debug_assert(params.size() == CREATURE_PARAMS_COUNT);
    int color = atoi(params[CREATURE_COLOR_INDEX].c_str());
    mana cost(params[CREATURE_COST_INDEX]);
    int attack = atoi(params[CREATURE_ATTACK_INDEX].c_str());
    int max_health = atoi(params[CREATURE_HEALTH_INDEX].c_str());
    std::vector<trait> vt;
    if(params[CREATURE_TRAITS_INDEX].length() > 0){
        std::vector<std::string> trait_strings = 
            split(params[CREATURE_TRAITS_INDEX],'|');
        vt.resize(trait_strings.size());
        for(unsigned long i=0; i<trait_strings.size(); i++){
            vt[i] = trait(trait_strings[i]);
        }
    }

    return Creature(params[CREATURE_NAME_INDEX],
                    color, attack, max_health,
                    cost, vt);
}
