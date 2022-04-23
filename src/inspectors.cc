#include "inspectors.h"

/* ========================================================================= 
 * ======================          STATICS            ======================
 * ========================================================================= */

static int longest(std::vector<std::string> options){
    int biggest = 0;
    for(auto s:options){
        if(s.length() > biggest) biggest = s.length();
    }
    return biggest;
}

/* ========================================================================= 
 * ======================       INSPECTOR_MENU        ======================
 * ========================================================================= */

inspector_menu::inspector_menu(int OG_width, int OG_height){
    std::vector<std::string> options = {
        "Effects",
        "Cards",
        "Decks",
        "Exit"
    };
    bool fullsize = false;
    if ((OG_height - 2) * 3 < options.size()*4) {
        /* if 75% of the OG_height is smaller than the amount of options from
           this menu, use the full screen size */
        fullsize = true;
    }else if ((OG_width - 2) * 3 < longest(options) * 4){
        /* if 75% of the OG_height is smaller than the amount of options from
           this menu, use the full screen size */
        fullsize = true;
    }

    if(fullsize){
        height = OG_height;
        width = OG_width;
    }else{
        height = (3 * OG_height) / 4;
        width = (3 * OG_width) / 4;
    }

    int diffH = OG_height - height, diffW = OG_width - width;

    win = newwin(height, width, diffH / 2, diffW / 2);
    pan = new_panel(win);
    box(win, 0, 0);
    keypad(win, true);

    menu.startup(win, options);

    update_panels();
    doupdate();
}

inspector_menu::~inspector_menu(){
    del_panel(pan);
    delwin(win);
    update_panels();
    doupdate();
}

void inspector_menu::move_menu(int key){
    menu.move_menu(key);
}

int inspector_menu::select_item(){
    return menu.select_item();
}

int inspector_menu::get_input(){
    return wgetch(win);
}

/* ========================================================================= 
 * ======================          FUNCTIONS          ======================
 * ========================================================================= */

void choose_inspector(){
    int x,y, input;
    getmaxyx(stdscr, y, x);
    inspector_menu menu(x, y);
    while(true){
        input = menu.get_input();
        switch (input) {
            case KEY_UP:
            case KEY_DOWN:
            case 'w':
            case 's':
                menu.move_menu(input);
                input = 0;
                break;
            case 10:
            case 'e':
                input = menu.select_item();
                break;
            case 'q':
                input = -1;
                break;
            default:
                input = 0;
        }
        /* check if something was selected with that input */
        switch (input) {
            case 0:
                break; /* we chose nothing */
            case -1:
                return; /* we chose to exit the menu */
            case 1:
            case 2:
            case 3:
                /* to be added */
                mvprintw(0,0,"a thing has been selected!");
                refresh();
                break;
            default:
                debug_assert_not_reached();
        }
    }
}

