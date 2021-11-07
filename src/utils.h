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

#define LOG(level, fmt, ...) (logger::get().log(level, fmt, __VA_ARGS__))

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

std::string cardTypeAsString(CardType type);

enum CardColors{
    WHITE =0x1,
    BLUE = 0x2,
    BLACK = 0x4,
    RED = 0x8,
    GREEN = 0x10,
    COLOR_MAX = 0x1f
};

std::string cardColorAsString(char color);

#endif /* _UTILS_H */
