#ifndef _MANA_H
#define _MANA_H

#include <string>
#include "utils.h"

/*
 * The mana string is in the format ([0-9]*)(W|U|B|R|G)
 * in this order
 * C: Colorless
 * W: White
 * U: blue
 * B: black
 * R: Red
 * G: Green
 *
 * Colorless mana can be explicitly demanded, instead of allowing any mana, so we have to have C and the number of generic mana
 *
 * it can also include hybrid mana, when creating a mana value,
 * however, when comparing if there is enough mana to
 * cast something, no hybrid mana is allowed
 */
class mana{
private:
    std::string s;
public:
    mana(std::string ss);

    bool has_hybrid();
    bool has_generic();

    int count_generic();

    bool operator>= (mana& m);
};


#endif /*_MANA_H*/
