#ifndef _TRAITS_H
#define _TRAITS_H

#include <string>
#include "utils.h"

enum trait_type{
    TRAIT_INVALID,
    TRAIT_FLY,
    TRAIT_REACH,
    TRAIT_HASTE,
    TRAIT_FIRST_STRIKE,
    TRAIT_OUT_FOR_BLOOD, /* must attack every turn */
};

class trait{
private:
    unsigned int time_left;
    trait_type type;
public:
    trait(trait_type = TRAIT_INVALID, unsigned int = 0);
    trait(std::string line);

    bool decrease(); /* returns whether the trait has finished */

    bool operator==(const trait other){
        debug_assert(type != TRAIT_INVALID);
        return type == other.type;
    }
    bool operator==(const trait_type tp){
        debug_assert(type != TRAIT_INVALID);
        return type == tp;
    }
};

trait_type traitTypeFromString(std::string);
std::string traitTypeAsString(trait_type);

#endif /* _TRAITS_H */
