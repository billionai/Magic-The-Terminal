#ifndef _LAND_H
#define _LAND_H

#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "card.h"
#include "mana.h"
#include "effects.h"

/* All lands generate mana, which is managed as an effect.
 * lands that can generate multiple types of mana (like gates)
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

Land make_Land(std::string line, std::unordered_map<std::string, Effect>);

enum land_params{
    LAND_NAME_INDEX,
    LAND_COLOR_INDEX,
    LAND_EFFECTS_INDEX,
    LAND_PARAMETERS
};

#endif /* _LAND_H */
