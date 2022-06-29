#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <stdexcept>

#include "log.h"
#include "graphic.h"
#include "main_menu.h"
#include "game_menu.h"
#include "inspectors.h"
#include "database.h"

void early_init(){
    start_effects();
    start_cards();
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
            case 1:
                card_game_loop();
                update_panels();
                doupdate();
                break;
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
    logger::get().openFile();
    try {
        start_graphics();
        captured_main();
    }
    catch(int err) {
        printw(0, 0, "an exception has occurred, press any key to exit");
        refresh();
    }
    logger::get().closeFile();
    finish_graphics(original);
    return 0;
}
