#ifndef _CARD_H
#define _CARD_H
#include <string>
#include "utils.h"

class Card{
private:
    bool tapped; //if the card is tapped

public:
    const CardType type;
    const std::string name;
    const char color;
    Card(CardType ct, std::string nam, char col):
        type(ct), name(nam), color(col) {
            LOG(DEBUG, "creating card %s, with color %d and type %s", name.c_str(), color, cardTypeAsString(type).c_str());
        }

    bool getTap();

    void tap();
    void untap();
};

#endif /* _CARD_H */
