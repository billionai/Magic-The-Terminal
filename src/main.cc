#include <stdio.h>
#include <vector>
#include <fstream>

#include "land.h"
#include "log.h"

#ifdef DEBUG_BUILD
#  define VERBOSITY DEBUG
#else
#  define VERBOSITY WARNING
#endif

void start_cards(std::vector<Card> &cards){
    /* TODO: Change this to include things to the sqlite database */
    std::ifstream cardFiles;
    std::string line, fName, dir = "cards/";

    //read all lands
    fName = dir + "lands";
    cardFiles.open(fName.c_str());
    debug_assert(cardFiles.is_open());
    getline(cardFiles, line); //remove header
    getline(cardFiles, line);
    while(!line.empty()){
        cards.push_back(Land(line, cards.size()));
        getline(cardFiles, line);
    }
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
