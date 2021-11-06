#ifndef _CARD_H
#define _CARD_H
#include <string>
#include "utils.h"

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
