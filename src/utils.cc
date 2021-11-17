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
    debug_assert_not_reached();
    return std::string("");
}

std::string cardColorAsString(char color){
    debug_assert(color < COLOR_MAX);
    if(color == 0)
        return std::string(" COLORLESS");
    std::string colString;
    if(color & WHITE) colString += " WHITE";
    if(color & BLUE) colString += " BLUE";
    if(color & BLACK) colString += " BLACK";
    if(color & RED) colString += " RED";
    if(color & GREEN) colString += " GREEN";
    return colString;
}

CardColors stringToColor(char c){
    switch(c){
        case 'W':
            return WHITE;
        case 'U':
            return BLUE;
        case 'B':
            return BLACK;
        case 'R':
            return RED;
        case 'G':
            return GREEN;
        case 'C':
            return COLORLESS;
        default:
            debug_assert_not_reached();
    }
    return COLORLESS;
}

char stringToColor(char c1, char c2){
    debug_assert(c1 != c2);
    return stringToColor(c1) | stringToColor(c2);
}

std::vector<std::string> split(std::string s, char delim){
    size_t pos=-1, new_pos;
    std::vector<std::string> ret;
    do{
        pos++;
        new_pos = s.find(delim, pos);
        ret.push_back(s.substr(pos, new_pos-pos));
        pos = new_pos;
    }while(pos != std::string::npos);
    return ret;
}
