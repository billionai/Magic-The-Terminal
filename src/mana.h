#ifndef _MANA_H
#define _MANA_H

#include "utils.h"

class mana{
public:
    const char color;
    const char amount;

    mana(const char col = 1, const char amnt = 1):
        color(col), amount(amnt) {
            debug_assert(col < COLOR_MAX);
        }
}

#endif /*_MANA_H*/
