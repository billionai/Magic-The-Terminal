#include "card.h"

void Card::tap(){
    debug_assert(!tapped);
    tapped = true;
}

void Card::untap(){
    tapped = false;
}
