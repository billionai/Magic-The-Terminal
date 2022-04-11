#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__
#include "graphic.h"

/* This class handles all the information important to main menus.
   It mostly handles updating and handling the screen, whereas inputs
   and calling other states are handled by the functions. */
class main_menu_info{
private:
    WINDOW* windows[2];
    PANEL* panels[2];
    bool has_logo;
public:
    main_menu_info();
    //~main_menu_info();
};

int handle_main_menu();

#endif /* __MAIN_MENU_H__ */
