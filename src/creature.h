#ifndef _CREATURE_H
#define _CREATURE_H

#include <unordered_map>

#include "mana.h"
#include "card.h"
#include "traits.h"
#include "effects.h"

class Creature: public Card{
private:
    const mana cost;
    const int attack;
    const int max_health;
    //TODO add card effects

    //these members can start with values, but they may be
    //changed as the game goes on
    std::vector<trait> traits;
    std::vector<complexEffect> effects;

    //members that can change easily in combat:
    
    //if this card has invocation sickness at this point
    bool invocation_sickness;
    //during a combat phase, this is important
    //after the combat phase, the health is back up to full
    int curr_health;
    /*TODO add counters as a struct like:
     * struct counter{
     *     counterType type;
     *     counterEffects c_effect;
     *     int amnt;
     * }
     * with validation that the effect applies to the counter type
     * see https://mtg.fandom.com/wiki/Counter_(marker)
     */
public:
    Creature(const std::string name,
             const char col,
             const int atk,
             const int mx_hp,
             const mana cst,
             std::vector<trait>&);
};

Creature make_Creature(std::string line, std::unordered_map<std::string, Effect>);

enum creature_params{
    CREATURE_NAME_INDEX,
    CREATURE_COLOR_INDEX,
    CREATURE_COST_INDEX,
    CREATURE_ATTACK_INDEX,
    CREATURE_HEALTH_INDEX,
    CREATURE_TRAITS_INDEX,
    CREATURE_EFFECTS_INDEX,
    CREATURE_TYPE_INDEX,
    CREATURE_PARAMS_COUNT
};

#endif /*_CREATURE_H*/
