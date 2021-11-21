#ifndef _UTILS_H
#define _UTILS_H

/* Useful utilities that many, if not most, files may need */

#include <assert.h>
#include <string>
#include <vector>

#include "log.h"

#ifdef DEBUG_BUILD
#  define debug_assert(condition) assert(condition)
#  define debug_assert_not_reached() __builtin_unreachable()
#else /* DEBUG_BUILD */
#  define debug_assert(condition) \
    do {\
        if(!(condition)) \
            logger::get().log(WARNING, "an assert was hit on function %s, file %s, line %d", __func__ , __FILE__, __LINE__);\
    }while(0)
#  define debug_assert_not_reached() \
    do {\
        logger::get().log(WARNING, "an assert was hit on function %s, file %s, line %d", __func__ , __FILE__, __LINE__);\
    }while(0);\
    __builtin_unreachable()
#endif /* DEBUG_BUILD */

#define ADD_BIT(store, bit) ((store) |= (1<<(bit)))
#define REMOVE_BIT(store, bit) ((store) &= ~(1<<(bit)))
#define CHECK_BIT(store, bit) (((store)>>(bit)) & 1)

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

std::string cardTypeAsString(CardType type);

enum CardColors{
    COLORLESS = 0,
    WHITE =0x1,
    BLUE = 0x2,
    BLACK = 0x4,
    RED = 0x8,
    GREEN = 0x10,
    COLOR_MAX = 0x1f
};

std::string cardColorAsString(char color);

//turn a single color character into a CardColor
CardColors stringToColor(char c);
//turn 2 color characters into a CardColor char
char stringToColor(char c1, char c2);

/* returns a vector with the split substring, without delimiter */
std::vector<std::string> split(std::string s, char delim);

#endif /* _UTILS_H */
