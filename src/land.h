#ifndef _LAND_H
#define _LAND_H

#include "card.h"

class Land: public Card {
private:
    const int max_mana; //how much mana this land generate
    //TODO add colored mana

    //if the card can generate mana as soon as it is played
    //gate and other special land cards cannot
    //but regular land can
    const bool starts_with_mana; 

public:
    Land(const int id,
         const std::string name,
         const char col,
         const bool start_mana,
         const int mx_mana):
            Card(LAND, id, name, col),
            starts_with_mana(mana),
            max_mana(mx_mana){
                if(!starts_with_mana)
                    tap();
            }
}

#endif /* _LAND_H */
