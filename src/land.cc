#include "land.h"

Land::Land(const std::string name,
     const char col,
     std::vector<complexEffect>&& e):
        Card(LAND, name, col),
        effects(std::move(e)) { }

Land make_Land(std::string line){
    std::vector<std::string> params = split(line, ',');
    Effect e = make_effect("name,0,ANYTIME,TAP,GENERATE_MANA,SELF,C,0");
    complexEffect ce(&e);
    std::vector<complexEffect> ef;
    ef.emplace_back(std::move(ce));
    return Land(params[0], atoi(params[1].c_str()), std::move(ef));
}
