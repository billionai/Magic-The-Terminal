#include <stdio.h>
//#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdexcept>

#include "land.h"
#include "creature.h"
#include "log.h"
#include "effects.h"
#include "deck.h"

#ifdef DEBUG_BUILD
#  define VERBOSITY DEBUG
#else
#  define VERBOSITY WARNING
#endif

#define READ_CARDS(Type, fname, map, output) do{\
    std::ifstream cardFile("database/" fname);\
    debug_assert(cardFile.is_open());\
    getline(cardFile, line);\
    getline(cardFile, line);\
    while(!line.empty()){\
        try{ \
            Type t = make_##Type(line, map);\
            debug_assert(output.count(t.name) == 0);\
            output.emplace(t.name, t);\
        }catch(const std::invalid_argument& a) {\
            /* error has already been reported, just ignore */\
        }\
        getline(cardFile, line);\
    }\
}while(0)

void start_cards(std::unordered_map<std::string, Card> &cards,
                 std::unordered_map<std::string, Effect> &map){
    std::ifstream cardFile;
    std::string line;
    /* TODO: Change this to include things to the sqlite database */
    READ_CARDS(Land, "lands", map, cards);
    READ_CARDS(Creature, "creatures", map, cards);
}

void start_effects(std::unordered_map<std::string, Effect> &map){
    std::ifstream effectsFile("database/effects");
    std::string line;
    debug_assert(effectsFile.is_open());
    getline(effectsFile, line);
    getline(effectsFile, line);
    while(!line.empty()){
        Effect e = make_effect(line);
        debug_assert(map.count(e.name) == 0);
        map.emplace(e.name, e);
        getline(effectsFile, line);
    }
}

int main(){
    //char* input;
    std::unordered_map<std::string, Card> all_cards;
    std::unordered_map<std::string, Effect> all_effects;
    logger::get().setVerbosity(VERBOSITY);
    start_effects(all_effects);
    start_cards(all_cards, all_effects);
    printf("Welcome to magic the terminal!\n\n");
    printf("We already have %ld card for you to play! Look:\n",all_cards.size());
    for(auto itr: all_cards){
        printf("%s\n", itr.first.c_str());
    }
    printf("\n\nCreating the goblin deck now:\n");
    deck d("goblin1", all_cards);
    d.print_ordered();
    d.print_short();
    //d.print_shuffle();
    return 0;
}
