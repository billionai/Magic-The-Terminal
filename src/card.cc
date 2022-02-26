#include "card.h"

void Card::tap(){
    debug_assert(!tapped);
    tapped = true;
}

void Card::untap(){
    tapped = false;
}

std::string Card::str(){
    std::string ret;
    ret = name + ": a ";
    ret += cardColorAsString(color);
    ret += cardTypeAsString(type);
    return ret;
}
