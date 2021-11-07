#include "utils.h"

std::string cardTypeAsString(CardType type) {
    switch(type){
        case INSTANT:
            return std::string("INSTANT");
        case SORCERY:
            return std::string("SORCERY");
        case LAND:
            return std::string("LAND");
        case CREATURE:
            return std::string("CREATURE");
        case ARTIFACT:
            return std::string("ARTIFACT");
        case ENCHANTMENT:
            return std::string("ENCHANTMENT");
        case PLANESWALKER:
            return std::string("PLANESWALKER");
    }
    debug_assert(false);
    return std::string("");
}

std::string cardColorAsString(char color){
    debug_assert(color < COLOR_MAX);
    std::string colString;
    if(color & WHITE) colString += " WHITE";
    if(color & BLUE) colString += " BLUE";
    if(color & BLACK) colString += " BLACK";
    if(color & RED) colString += " RED";
    if(color & GREEN) colString += " GREEN";
    return colString;
}
