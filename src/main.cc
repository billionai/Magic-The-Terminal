#include <stdio.h>
//#include <vector>
#include <unordered_map>
#include <fstream>

#include "land.h"
#include "creature.h"
#include "log.h"
#include "effects.h"

#ifdef DEBUG_BUILD
#  define VERBOSITY DEBUG
#else
#  define VERBOSITY WARNING
#endif

#define READ_CARDS(Type, fname, output) do{\
    std::ifstream cardFile("database/" fname);\
    debug_assert(cardFile.is_open());\
    getline(cardFile, line);\
    getline(cardFile, line);\
    while(!line.empty()){\
        Type t = make_##Type(line);\
        debug_assert(output.count(t.name) == 0);\
        output.emplace(t.name, t);\
        getline(cardFile, line);\
    }\
}while(0)

void start_cards(std::unordered_map<std::string, Card> &cards){
    std::ifstream cardFile;
    std::string line;
    /* TODO: Change this to include things to the sqlite database */
    READ_CARDS(Land, "lands", cards);
    READ_CARDS(Creature, "creatures", cards);
}

int main(){
    std::unordered_map<std::string, Card> all_cards;
    logger::get().setVerbosity(VERBOSITY);
    start_cards(all_cards);
    printf("Welcome to magic the terminal!\n\n");
    for(auto card: all_cards){
        printf("%s\ncard type: %s, card colors:%s\n", card.second.name.c_str(),
                            cardTypeAsString(card.second.type).c_str(), cardColorAsString(card.second.color).c_str());
    }
    return 0;
}
