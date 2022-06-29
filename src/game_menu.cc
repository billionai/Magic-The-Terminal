#include "game_menu.h"

game_menu::game_menu()
    : menu () {
    std::vector<std::string> options ={
        "1 player game",
        "2 player game",
        "return"
    };

    int x, y;
    getmaxyx(stdscr, y, x);
    windows = newwin(y, x, 0, 0);
    panels = new_panel(windows);
    box(windows, 0, 0);
    keypad(windows, true);

    menu.startup(windows, options);

    update_panels();
    doupdate();
}

game_menu::~game_menu(){
    del_panel(panels);
    delwin(windows);
}

void game_menu::move_menu(int key) {
    menu.move_menu(key);
}

int game_menu::select_item(){
    return menu.select_item();
}

int game_menu::get_input(){
    return wgetch(windows);
}

//================= FINISH GAME_MENU CLASS =============================

void card_game_loop (){
    game_menu m;
    int c, selected = 0;
    while(selected == 0) {
        c = m.get_input();
        switch (c) {
            case KEY_UP:
            case KEY_DOWN:
            case 'j':
            case 'k':
            case 'w':
            case 's':
                m.move_menu(c);
                break;
            case '\n':
            case ' ':
            case 'e':
                selected = m.select_item();
                break;
            case 'q':
                selected = -1;
                break;
            default:
                /* unknown key was pressed, do nothing.  */
                break;
        }
        switch(selected) {
            case -1:
                /* Quit was chosen.  Exit the function.  */
                return;
            case 0:
                /* No option was selected.  */
                break;
            default:
                mvprintw(0,0, "Not yet implemented");
                refresh();
                break;
        }
        selected = 0;
    }
}
