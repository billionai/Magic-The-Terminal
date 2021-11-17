#ifndef _LAND_H
#define _LAND_H

#include <stdlib.h>
#include <vector>
#include "card.h"
#include "mana.h"
#include "effects.h"

/* All lands generate mana, which is managed as an effect.
 * lands that can generate multiple times of mana (like gates)
 * will have multiple complex effects.  Lands that generate
 * more than one mana will have one complexEffect chain, where
 * the first effect has a cost of tapping, and is not
 * mandatory, and all others are free and mandatory.
 *
 * Lands that start tapped must have the effect enter_tapped,
 * which is a free and mandatory effect that taps the card as
 * it enters the battlefield.
 */

class Land: public Card {
private:
    std::vector<complexEffect> effects;

public:
    Land(const std::string name,
         const char col,
         std::vector<complexEffect>&& e);
};

Land make_Land(std::string line);

#endif /* _LAND_H */
