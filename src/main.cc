#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <stdexcept>

#include "land.h"
#include "creature.h"
#include "log.h"
#include "effects.h"
#include "deck.h"
#include "graphic.h"
#include "main_menu.h"
#include "inspectors.h"

/* global variables, they work as the database for now. */
/* FIXME: Turn this into an actual database, with accessors and such.
   it will be needed at some point. */
std::unordered_map<std::string, Card> all_cards;
std::unordered_map<std::string, Effect> all_effects;

#ifdef DEBUG_BUILD
#  define VERBOSITY WARNING
#else
#  define VERBOSITY FAILURE
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

void early_init(){
    start_effects(all_effects);
    start_cards(all_cards, all_effects);
}

void captured_main() {
    main_menu_info info;
    early_init();
    int c, selected = 0;
    while(selected == 0) {
        c = info.get_input();
        switch (c) {
            case KEY_UP:
            case KEY_DOWN:
            case 'j':
            case 'k':
            case 'w':
            case 's':
                info.move_menu(c);
                break;
            case '\n':
            case ' ':
            case 'e':
                selected = info.select_item();
                break;
            case 'q':
                selected = -1;
                break;
            default:
                /* do nothing */
                break;
        }
        switch (selected) {
            case 2:
                choose_inspector();
                break;
            case -1:
                /* quit was chosen. Exit the function */
                return;
            case 0:
                /* Do nothing, no option was selected */
                break;
            default:
                mvprintw(0,0,"not yet implemented, press any key to continue");
                refresh();
        }
        selected = 0;
    }
}

int main(){
    terminal_options original = get_terminal_options();
    logger::get().setVerbosity(VERBOSITY);
    try {
        start_graphics();
        captured_main();
    }
    catch(int err) {
        printw(0, 0, "an exception has occurred, press any key to exit");
        refresh();
    }
    finish_graphics(original);
    return 0;
}
