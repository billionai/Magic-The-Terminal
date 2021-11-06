#ifndef _CARD_H
#define _CARD_H
#include <string>
#include "utils.h"

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

enum CardColors{
    WHITE =0x1,
    BLUE = 0x2,
    BLACK = 0x4,
    RED = 0x8,
    GREEN = 0x10
};

class Card{
public:
    const CardType type;
    const int ID;
    const std::string name;
    const char color;
    Card(CardType ct, int id, std::string nam, char col):
        type(ct), ID(id), name(nam), color(col) { }
};

#endif /* _CARD_H */
