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

std::string getCSVColumn(std::string line, int column){
    LOG(DEBUG, "getting column %d of line %s", column, line.c_str());
    if(column == 0)
        return line.substr(0, line.find(','));
    int curr = 0;
    std::size_t pos;
    while(curr < column){
        pos = line.find(',');

        //this assert only fails if column greater than the amount of columns of line
        debug_assert(pos != std::string::npos);
        //ignore the previous column
        line = line.substr(pos+1);
        curr++;
    }
    //the first remaining column is the desired column
    //just need to get rid of the rest of the string
    pos = line.find(',');
    if(pos == std::string::npos){
        //the requested column is the last one. remove \n if it is there
        pos = line.find('\n');
        if(pos == std::string::npos)
            return line;
        return line.substr(0,pos);
    }
    return line.substr(0,pos);
}
