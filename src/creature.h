#ifndef _CREATURE_H
#define _CREATURE_H

#include "mana.h"
#include "card.h"

class Creature: public Card{
private:
    const mana cost;
    const int attack;
    const int max_health;
    //TODO add card effects

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
             const mana cst);
};

Creature make_Creature(std::string line);

#endif /*_CREATURE_H*/
