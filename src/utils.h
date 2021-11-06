#ifndef _UTILS_H
#define _UTILS_H

/* Useful utilities that many, if not most, files may need */

#include <assert.h>
#include <string>

#include "log.h"

#ifdef DEBUG_BUILD
#  define debug_assert(condition) assert(condition)
#else /* DEBUG_BUILD */
#  define debug_assert(condition) \
    do {\
        if(!(condition)) \
            logger::get().log(WARNING, "an assert was hit on function %s, file %s, line %d", __func__ , __FILE__, __LINE__);\
    }while(0)
#endif /* DEBUG_BUILD */

#define IS_PERMANENT(cardType) (cardType > 0)

enum CardType{
    /* non-permanent cards must be <0 */
    INSTANT = -2,
    SORCERY = -1,
    /* permanent cards must be >0 */
    LAND = 1,
    CREATURE,
    ARTIFACT,
    ENCHANTMENT,
    PLANESWALKER
};

std::string cardTypeAsString(CardType type) {
    switch(type){
        case INSTANT:
            return std::string("INSTANT");
        case SORCERY:
            return std::string("SORCERY");
        case LAND:
            return std::string("LAND");
        case CREATURE:
            return std::string("CREATURE");
        case ARTIFACT:
            return std::string("ARTIFACT");
        case ENCHANTMENT:
            return std::string("ENCHANTMENT");
        case PLANESWALKER:
            return std::string("PLANESWALKER");
    }
    debug_assert(false);
    return std::string("");
}

enum CardColors{
    WHITE =0x1,
    BLUE = 0x2,
    BLACK = 0x4,
    RED = 0x8,
    GREEN = 0x10,
    COLOR_MAX = 0x1f
};

std::string cardColorAsString(char color){
    debug_assert(color < COLOR_MAX);
    std::string colString;
    if(color & WHITE) colString += " WHITE";
    if(color & BLUE) colString += " BLUE";
    if(color & BLACK) colString += " BLACK";
    if(color & RED) colString += " RED";
    if(color & GREEN) colString += " GREEN";
    return colString;
}

#endif /* _UTILS_H */
