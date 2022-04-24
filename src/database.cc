#include <unordered_map>
#include <fstream>

#include "land.h"
#include "creature.h"
#include "effects.h"
#include "deck.h"
#include "log.h"
#include "database.h"

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


/* global variables, they work as the database for now. */
/* FIXME: Turn this into an actual database, with accessors and such.
   it will be needed at some point. */
std::unordered_map<std::string, Card> all_cards;
std::unordered_map<std::string, Effect> all_effects;

void start_cards(){
    std::ifstream cardFile;
    std::string line;
    /* TODO: Change this to include things to the sqlite database */
    READ_CARDS(Land, "lands", all_effects, all_cards);
    READ_CARDS(Creature, "creatures", all_effects, all_cards);
}

void start_effects(){
    std::ifstream effectsFile("database/effects");
    std::string line;
    debug_assert(effectsFile.is_open());
    getline(effectsFile, line);
    getline(effectsFile, line);
    while(!line.empty()){
        Effect e = make_effect(line);
        debug_assert(all_effects.count(e.name) == 0);
        all_effects.emplace(e.name, e);
        getline(effectsFile, line);
    }
}

const std::unordered_map<std::string, Effect>& get_effect_database(){
    return all_effects;
}

const std::unordered_map<std::string, Card>& get_card_database(){
    return all_cards;
}
