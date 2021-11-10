#ifndef _LAND_H
#define _LAND_H

#include <stdlib.h>
#include <vector>
#include "card.h"
#include "mana.h"

class Land: public Card {
private:
    const mana max_mana; //how much mana this land generate

    //if the card can generate mana as soon as it is played
    //gate and other special land cards cannot
    //but regular land can
    const bool starts_with_mana; 

public:
    Land(const int id,
         const std::string name,
         const char col,
         const bool start_mana,
         const mana mx_mana):
            Card(LAND, id, name, col),
            max_mana(mx_mana),
            starts_with_mana(start_mana) { }

    Land(const std::string& line, const int id):
        Card(LAND, id,
             getCSVColumn(line, 0),
             atoi(getCSVColumn(line, 1).c_str())),
        max_mana(getCSVColumn(line, 2)),
        starts_with_mana(getCSVColumn(line, 3)[0] != '0') { }
};

#endif /* _LAND_H */
