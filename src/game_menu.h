#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

#include "graphic.h"
#include "menu.h"

/* This class handles all the information important to the game menu.
   It handles deciding when and how to start the game, getting the
   input from the user and calling the main loop.  */
class game_menu{
private:
    WINDOW* windows;
    PANEL* panels;
    managed_menu menu;
public:
    game_menu();
    ~game_menu();
    void move_menu(int key);
    int select_item();
    int get_input();
};

void card_game_loop ();

#endif /* __GAME_MENU_H__ */
