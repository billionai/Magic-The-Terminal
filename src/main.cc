#include <stdio.h>
#include <vector>
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
        cards.push_back(make_##Type(line));\
        getline(cardFile, line);\
    }\
}while(0)

void start_cards(std::vector<Card> &cards){
    std::ifstream cardFile;
    std::string line;
    /* TODO: Change this to include things to the sqlite database */
    READ_CARDS(Land, "lands", cards);
    //READ_CARDS(Creature, "creatures", cards);
}

int main(){
    std::vector<Card> all_cards;
    logger::get().setVerbosity(VERBOSITY);
    start_cards(all_cards);
    printf("Welcome to magic the terminal!\n\n");
    for(auto card: all_cards){
        printf("%s\ncard type: %s, card ID: %d, card colors:%s\n", card.name.c_str(),
                            cardTypeAsString(card.type).c_str(), card.ID, cardColorAsString(card.color).c_str());
    }
    return 0;
}
