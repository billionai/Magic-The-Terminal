#include "land.h"

Land::Land(const std::string name,
     const char col,
     std::vector<complexEffect> e):
        Card(LAND, name, col),
        effects(e) { }

Land make_Land(std::string line){
    std::string name(getCSVColumn(line, 0));
    int col = atoi(getCSVColumn(line, 1).c_str());
    std::vector<std::string> effs = split(getCSVColumn(line, 2), '|');
    //making a dummy effect, just to test generation
    Effect e = make_effect("name,0,ANYTIME,TAP,GENERATE_MANA,SELF,C,0");
    complexEffect ce(&e);
    std::vector<complexEffect> ef;
    ef.emplace_back(std::move(ce));
    return Land(name, col, ef);
}
