#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__
#include "graphic.h"

#include <vector>
#include <string>

/* Helper class to display selected menu items */
class main_menu_item{
private:
    /* Where this option will be printed */
    int line, column;
    std::string text;
public:
    main_menu_item(){}
    main_menu_item(int l, int c, std::string t):
        line(l), column(c), text(t) { }

    void set(int l, int c, std::string t){
        line = l;
        column = c;
        text = t;
    }

    void print(WINDOW* w){
        mvwprintw(w, line, column, text.c_str());
    }
};

/* This class handles all the information important to main menus.
   It mostly handles updating and handling the screen, whereas inputs
   and calling other states are handled by the functions. */
class main_menu_info{
private:
    WINDOW* windows[2];
    PANEL* panels[2];
    bool has_logo;
    ITEM** bare_menu_items;
    std::vector<main_menu_item> class_menu_items;
    MENU* menu;
public:
    main_menu_info();
    //~main_menu_info();
    void move_menu(int key);
    int select_item();
};

#endif /* __MAIN_MENU_H__ */
