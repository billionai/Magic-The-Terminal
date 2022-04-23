#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include <vector>
#include "graphic.h"

/* Helper class to display selected menu items */
class menu_item{
private:
    /* Where this option will be printed */
    int line, column;
    std::string text;
public:
    menu_item(){}
    menu_item(int l, int c, std::string t):
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

class managed_menu{
private:
    WINDOW* menu_win;
    ITEM** bare_menu_items;
    std::vector<menu_item> class_menu_items;
    MENU* menu;
    bool started;
public:
    managed_menu();
    /* this constructor just calls startup, check that for information */
    managed_menu(WINDOW*, std::vector<std::string>);
    ~managed_menu();

    /* This method receives a pointer for the windows where the menu will be displayed
       and a vector of all the options. it calculates where option texts should go and manages
       the full menu interface from ncurses */
    void startup(WINDOW*, std::vector<std::string>);

    void move_menu(int key);
    int select_item();
};

#endif /* __MENU_H__ */
